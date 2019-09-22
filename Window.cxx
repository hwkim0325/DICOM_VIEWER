
#include "Window.h"
#include "ui_Window.h"

#include <qfiledialog.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qfileinfo.h>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <vtkImageData.h>

#include <itkGDCMImageIO.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkImageToVTKImageFilter.h>

#include <vtkSmartPointer.h>
#include <vtkNew.h>

#include <vtkImageMapper.h>
#include <vtkActor2D.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCamera.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkRenderWindowInteractor.h>



Window::Window()
{
	this->ui = new Ui_QWindow;
	this->ui->setupUi(this);

	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow1;
	this->ui->view1->SetRenderWindow(renderWindow1);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow2;
	this->ui->view2_1->SetRenderWindow(renderWindow2);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow3;
	this->ui->view2_2->SetRenderWindow(renderWindow3);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow4;
	this->ui->view2_3->SetRenderWindow(renderWindow4);
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow5;
	this->ui->view2_4->SetRenderWindow(renderWindow5);

	this->ui->view1->GetRenderWindow()->Start();
	this->ui->view2_1->GetRenderWindow()->Start();
	this->ui->view2_2->GetRenderWindow()->Start();
	this->ui->view2_3->GetRenderWindow()->Start();
	this->ui->view2_4->GetRenderWindow()->Start();


	vtkNew<vtkEventQtSlotConnect> slotConnector;
	this->Connections = slotConnector;

	this->Connections->Connect(
		this->ui->view1->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseWheelForwardEvent, 
		this, 
		SLOT(mouseWheelUpEvent(vtkObject*, unsigned long, void*, void*))
	);
	this->Connections->Connect(
		this->ui->view1->GetRenderWindow()->GetInteractor(),
		vtkCommand::MouseWheelBackwardEvent, 
		this, 
		SLOT(mouseWheelDownEvent(vtkObject*, unsigned long, void*, void*))
	);

	connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(openSingleFile()));
	connect(this->ui->actionOpenDicomDir, SIGNAL(triggered()), this, SLOT(openFiles()));
	connect(this->ui->actionAbout_Dicom_Viewer, SIGNAL(triggered()), this, SLOT(getInformation()));
	connect(this->ui->listWidget, SIGNAL(itemSelectionChanged()),
		this, SLOT(ItemEvent()));
}

void Window::readDicomFile()
{
	dicomFileReader = dicomFileReaderType::New();
	dicomIO = GDCMImageType::New();
	dicomFileReader->SetFileName(dicomFile.toLocal8Bit().constData());
	dicomFileReader->SetImageIO(dicomIO);
	
	try
	{
		dicomFileReader->Update();
		canRead = true;
	}
	catch (itk::ExceptionObject & e)
	{
		canRead = false;
	}

}

void Window::readDicomDir()
{
	dicomDirReader = dicomDirReaderType::New();
	dicomIO = GDCMImageType::New();
	dicomDirReader->SetImageIO(dicomIO);
	
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetInputDirectory(dicomDir.toLocal8Bit().constData());

	const FileNamesContainer & fileNames = nameGenerator->GetInputFileNames();

	dicomDirReader->SetFileNames(fileNames);
	
	try
	{
		dicomDirReader->Update();
		canRead = true;
	}	
	catch (itk::ExceptionObject & e)
	{
		canRead = false;
	}
}

void Window::readDicom2D()
{
	ShiftScaleType::Pointer shiftFilter = ShiftScaleType::New();
	shiftFilter->SetInput(dicomFileReader->GetOutput());

	std::string interceptTagkey = "0028|1052";
	std::string slopeTagkey = "0028|1053";
	std::string interceptLabelId;
	std::string slopeLabelId;
	if (itk::GDCMImageIO::GetLabelFromTag(interceptTagkey, interceptLabelId)
		&& itk::GDCMImageIO::GetLabelFromTag(slopeTagkey, slopeLabelId))
	{
		std::string value1;
		std::string value2;

		if (dicomIO->GetValueFromTag(interceptTagkey, value1)
			&& dicomIO->GetValueFromTag(slopeTagkey, value2))
		{
			int intercept = std::stoi(value1);
			int slope = std::stoi(value2);

			shiftFilter->SetShift(intercept);
			shiftFilter->SetScale(slope);
		}
	}
	
	shiftFilter->Update();

	RescaleFilterType2D::Pointer rescaleFilter
		= RescaleFilterType2D::New();
	rescaleFilter->SetInput(shiftFilter->GetOutput());
	//rescaleFilter->SetOutputMinimum(0);
	//rescaleFilter->SetOutputMaximum(255);
	rescaleFilter->Update();

	IntensityWindowingImageFilterType::Pointer windowingFilter =
		IntensityWindowingImageFilterType::New();

	std::string centerTagkey = "0028|1050";
	std::string widthTagkey = "0028|1051";
	std::string centerLabelId;
	std::string widthLabelId;
	if (itk::GDCMImageIO::GetLabelFromTag(centerTagkey, centerLabelId)
		&& itk::GDCMImageIO::GetLabelFromTag(widthTagkey, widthLabelId))
	{
		std::string value1;
		std::string value2;
		std::string centerVal;
		std::string widthVal;
		if (dicomIO->GetValueFromTag(centerTagkey, value1)
			&& dicomIO->GetValueFromTag(widthTagkey, value2))
		{
			if (value1.find('\\') != value1.length())
				centerVal = value1.substr(0, value1.find('\\'));
			else
				centerVal = value1;
			if (value2.find('\\') != value1.length())
				widthVal = value2.substr(0, value2.find('\\'));
			else
				widthVal = value2;

			const ShortPixelType& center = (short)std::stoi(centerVal);
			const ShortPixelType& width = (short)std::stoi(widthVal);
			
			windowingFilter->SetWindowLevel(width, center);
			windowingFilter->SetWindowMinimum(0);
			windowingFilter->SetWindowMaximum(100);
			windowingFilter->SetOutputMinimum(0);
			windowingFilter->SetOutputMaximum(255);
		}
	}

	windowingFilter->SetInput(rescaleFilter->GetOutput());
	windowingFilter->Update();

	ResampleFilterType::Pointer resampler = ResampleFilterType::New();

	TransformType::Pointer transform = TransformType::New();
	TransformType::OutputVectorType translation;

	std::string posTagkey = "0020|0032";
	std::string posLabelId;
	if (itk::GDCMImageIO::GetLabelFromTag(posTagkey, posLabelId))
	{
		std::string value;
		std::string xPosValue;
		std::string yPosValue;
		if (dicomIO->GetValueFromTag(posTagkey, value))
		{
			auto firstPos = value.find_first_of('\\');
			xPosValue = value.substr(0, firstPos);
			auto secondPos = value.rfind('\\');
			yPosValue = value.substr(firstPos + 1, secondPos-firstPos-1);

			int xPos = std::stoi(xPosValue);
			int yPos = std::stoi(yPosValue);
			translation[0] = xPos;
			translation[1] = yPos;
		}
	}
	transform->Translate(translation);
	resampler->SetTransform(transform);
	
	InterpolatorType::Pointer interpolator = InterpolatorType::New();
	resampler->SetInterpolator(interpolator);
	resampler->SetDefaultPixelValue(0);


	std::string spacingTagkey = "0028|0030";
	std::string spacingLabelId;
	double PixelSpacingX;
	double PixelSpacingY;
	if (itk::GDCMImageIO::GetLabelFromTag(spacingTagkey, spacingLabelId))
	{
		std::string value;
		if (dicomIO->GetValueFromTag(spacingTagkey, value))
		{

			size_t border = value.find('\\');
			size_t length = value.length();
			std::string spacingValueX = value.substr(0, border);
			std::string spacingValueY = value.substr(border + 1, length - border -1);

			PixelSpacingX = std::stod(spacingValueX);
			PixelSpacingY = std::stod(spacingValueY);
		}
	}

	const double spacing[Dimension_2D] = { PixelSpacingX, PixelSpacingY };
	resampler->SetOutputSpacing(spacing);

	const double origin[Dimension_2D] = { 0.0,0.0 };
	resampler->SetOutputOrigin(origin);

	Short2DImageType::DirectionType direction;
	direction.SetIdentity();
	resampler->SetOutputDirection(direction);
	
	Short2DImageType::SizeType size;
	size[0] = this->ui->view1->width();
	size[1] = this->ui->view1->height();
	resampler->SetSize(size);
	
	resampler->SetInput(windowingFilter->GetOutput());

	CastingFilterType2D::Pointer caster
		= CastingFilterType2D::New();
	caster->SetInput(resampler->GetOutput());

	ConvertFilterType2D::Pointer convertor
		= ConvertFilterType2D::New();
	convertor->SetInput(caster->GetOutput());

	try
	{
		convertor->Update();
	}
	catch (itk::ExceptionObject & e)
	{
		std::cerr << "exception in file reader " << std::endl;
		std::cerr << e << std::endl;
	}

	/*vtkSmartPointer <vtkImageFlip> Flip
		= vtkSmartPointer <vtkImageFlip> ::New();
	Flip->SetInputData(convertor->GetOutput());
	Flip->SetFilteredAxis(1);
	Flip->Update();*/

	vtkSmartPointer<vtkImageData> ImageData
		= vtkSmartPointer<vtkImageData>::New();
	ImageData->DeepCopy(convertor->GetOutput());

	vtkSmartPointer<vtkImageMapper>	mapper
		= vtkSmartPointer<vtkImageMapper>::New();
	mapper->SetInputData(ImageData);

	vtkSmartPointer<vtkActor2D> actor
		= vtkSmartPointer<vtkActor2D>::New();
	actor->SetMapper(mapper);

	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor2D(actor);
	renderer->ResetCamera();

	this->ui->view1->GetRenderWindow()->AddRenderer(renderer);
	this->ui->view1->GetRenderWindow()->Render();
}

void Window::readDicom3D()
{
	RescaleFilterType3D::Pointer rescaleFilter
		= RescaleFilterType3D::New();
	rescaleFilter->SetInput(dicomDirReader->GetOutput());
	rescaleFilter->SetOutputMinimum(0);
	rescaleFilter->SetOutputMaximum(255);
	rescaleFilter->Update();

	CastingFilterType3D::Pointer caster
		= CastingFilterType3D::New();
	caster->SetInput(rescaleFilter->GetOutput());

	ConvertFilterType3D::Pointer filter
		= ConvertFilterType3D::New();
	filter->SetInput(caster->GetOutput());

	try
	{
		filter->Update();
	}
	catch (itk::ExceptionObject & e)
	{
		std::cerr << "exception in file reader " << std::endl;
		std::cerr << e << std::endl;
	}


	// should be deleted
	vtkSmartPointer <vtkImageFlip> Flip
		= vtkSmartPointer <vtkImageFlip> ::New();
	Flip->SetInputData(filter->GetOutput());
	Flip->SetFilteredAxis(1);
	Flip->Update();

	vtkSmartPointer<vtkImageData> ImageData
		= vtkSmartPointer<vtkImageData>::New();
	ImageData->DeepCopy(Flip->GetOutput());

	vtkSmartPointer<vtkImageMapper>	mapper
		= vtkSmartPointer<vtkImageMapper>::New();
	mapper->SetInputData(ImageData);
	mapper->SetColorWindow(350);
	mapper->SetColorLevel(50);

	vtkSmartPointer<vtkActor2D> actor
		= vtkSmartPointer<vtkActor2D>::New();
	actor->SetMapper(mapper);

	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor2D(actor);
	renderer->ResetCamera();

	this->ui->view1->GetRenderWindow()->AddRenderer(renderer);
	this->ui->view1->GetRenderWindow()->Render();
}

void Window::readDicom2DHeader()
{

	const DictionaryType& dictionary = dicomIO->GetMetaDataDictionary();

	auto itr = dictionary.Begin();
	auto end = dictionary.End();

	int size = 0;
	while (itr != end)
	{
		size++;
		itr++;
	}

	itr = dictionary.Begin();
	this->ui->tableWidget->setRowCount(size);

	int row = 0;

	while (itr != end)
	{
		itk::MetaDataObjectBase::Pointer entry = itr->second;
		MetaDataStringType::Pointer entryvalue =
			dynamic_cast<MetaDataStringType*> (entry.GetPointer());
		if (entryvalue)
		{

			std::string tagkey = itr->first;
			std::string labelId;
			bool found = itk::GDCMImageIO::GetLabelFromTag(tagkey, labelId);
			std::string tagvalue = entryvalue->GetMetaDataObjectValue();

			QTableWidgetItem* key = new QTableWidgetItem();
			QTableWidgetItem* description = new QTableWidgetItem();
			QTableWidgetItem* value = new QTableWidgetItem();
			
			QString qkey = QString::fromStdString(tagkey);
			QString qdescription = QString::fromStdString(labelId);
			QString qvalue = QString::fromStdString(tagvalue);

			key->setText(qkey);
			description->setText(qdescription);
			value->setText(qvalue);

			this->ui->tableWidget->setItem(row, 0, key);
			this->ui->tableWidget->setItem(row, 1, description);
			this->ui->tableWidget->setItem(row, 2, value);

			++itr;
			++row;
		}
	}

	

	//// Find specific data

	//std::string entryId = "0010|0010";
	//auto tagItr = dictionary.Find(entryId);
	//if (tagItr != end)
	//{
	//	MetaDataStringType::ConstPointer entryvalue =
	//		dynamic_cast<const MetaDataStringType*>(tagItr->second.GetPointer());
	//	
	//	if (entryvalue)
	//	{
	//		std::string tagvalue = entryvalue->GetMetaDataObjectValue();
	//		std::cout << "Patrint's Name ( " << entryId << ") ";
	//		std::cout << "is: " << tagvalue.c_str() << std::endl;
	//	}

	//// another way

	//	std::string tagkey = "0008|1050";
	//	std::string labelId;
	//	if (itk::GDCMImageIO::GetLabelFromTag(tagkey, labelId))
	//	{
	//		std::string value;
	//		std::cout << labelId << " (" << tagkey << "): ";
	//		if (gdcmImageIO->GetValueFromTag(tagkey, value))
	//		{
	//			std::cout << value;
	//		}
	//		else
	//		{
	//			std::cout << "(No Value Found in File)";
	//		}
	//		std::cout << std::endl;
	//	}
	//	else
	//	{
	//		std::cerr << "Trying to access inexistant DICOM tag." << std::endl;
	//	}
	//}
}


void Window::readDicom3DHeader()
{
	const DictionaryType & dictionary = dicomIO->GetMetaDataDictionary();

	auto itr = dictionary.Begin();
	auto end = dictionary.End();

	while (itr != end)
	{
		itk::MetaDataObjectBase::Pointer  entry = itr->second;
		MetaDataStringType::Pointer entryvalue =
			dynamic_cast<MetaDataStringType *>(entry.GetPointer());
		if (entryvalue)
		{
			std::string tagkey = itr->first;
			std::string tagvalue = entryvalue->GetMetaDataObjectValue();
			std::cout << tagkey << " = " << tagvalue << std::endl;
		}
		++itr;
	}

	// find specific data
	/*std::string entryId = "0010|0010";
	auto tagItr = dictionary.Find(entryId);
	if (tagItr == end)
	{
	std::cerr << "Tag" << entryId;
	std::cerr << "not found in the DICOM header" << std::endl;
	}
	MetaDataStringType::ConstPointer entryvalue =
	dynamic_cast<const MetaDataStringType *>(tagItr->second.GetPointer());

	if (entryvalue)
	{
	std::string tagvalue = entryvalue->GetMetaDataObjectValue();
	std::cout << "Patrint's Name ( " << entryId << " )";
	std::cout << " is: " << tagvalue << std::endl;
	}
	else
	{
	std::cerr << "Entry was not of string type" << std::endl;
	}*/


	// Change header file
	/*for (int i = 3; i < 5; i += 2)
	{
	std::string entryId("IDvalue[i]");
	std::string value("value[i]");
	itk::EncapsulateMetaData<std::string>(dictionary, entryId, value);
	}*/
}

void Window::slotExit()
{
	qApp->exit();
}

void Window::openSingleFile()
{
	QString filter = "All File (*.*) ;; Dicom File (*.dcm)";
	dicomFile =	QFileDialog::getOpenFileName(
		this, "Open File", QDir::homePath(),filter);

	QFileInfo SingleDir(dicomFile);

	if (dicomFile != NULL)
	{
		readDicomFile();
		if (canRead == true)
			this->ui->listWidget->addItem(SingleDir.fileName());
		if (this->ui->listWidget->count() == 0)
			QMessageBox::warning(this, "NO Dicom File", "Please select Dicom File");
	}

	if (this->ui->listWidget->count() != 0)
	{
		readDicom2D();
		readDicom2DHeader();
	}
}

void Window::openFiles()
{
	dicomDir = QFileDialog::getExistingDirectory(
		0, "Open Folder", QDir::currentPath());
	QDir dir(dicomDir);
	dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

	this->ui->listWidget->clear();
	
	QFileInfoList fileInfoList = dir.entryInfoList();

	if (dicomDir != NULL)
	{
		foreach(QFileInfo item, fileInfoList) {
			dicomFile = item.absoluteFilePath();
			readDicomFile();
			if (canRead == true)
			{
				QListWidgetItem* newitem = new QListWidgetItem();
				newitem->setText(item.fileName());

				QVariant filePathData(item.absoluteFilePath());
				newitem->setData(Qt::UserRole, filePathData);
				this->ui->listWidget->addItem(newitem);				
			}
		}
		if (this->ui->listWidget->count() == 0)
			QMessageBox::warning(this, "NO Dicom File", "Please select Dicom File");
		else
			dicomFile = fileInfoList.begin()->absoluteFilePath();
	}

	if (this->ui->listWidget->count() != 0)
	{
		readDicom2D();
		readDicom2DHeader();
	}
}

void Window::ItemEvent()
{
	dicomFile = this->ui->listWidget->currentItem()->data(Qt::UserRole).toString();
	readDicomFile();
	readDicom2D();
	readDicom2DHeader();
}

void Window::mouseWheelUpEvent(vtkObject*, unsigned long, void*, void*)
{
	int currentIndex = this->ui->listWidget->currentRow();
	if(currentIndex != 0)
	this->ui->listWidget->setCurrentRow(currentIndex - 1);
}

void Window::mouseWheelDownEvent(vtkObject*, unsigned long, void*, void*)
{
	int currentIndex = this->ui->listWidget->currentRow();
	if (currentIndex < this->ui->listWidget->count() - 1)
	this->ui->listWidget->setCurrentRow(currentIndex + 1);
}

void Window::getInformation()
{
	QMessageBox::about(this, "DICOM_VIEWER", 
		"\nThis is my first program\n"
		"the program name is 'DICOM_VIEWER'\n"
		"This is programmed for graduate project\n\n"
		"But it is not complete result\n"
		"I wanna program it more useful\n"
		"as much as another commercialized tool\n"
		"So it could have some tricky problem\n"
		"thanks for watching my fool window program\n\n"
		"\tTHANK YOU   (^ ^)  (_ _)\t\n");
}

Window::~Window()
{
	delete ui;
}
