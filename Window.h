#ifndef QWINDOW_H
#define QWINDOW_H

#include <memory>

#include <qmainwindow.h>
#include <qlistwidget.h>

#include <vtkObject.h>

#include "ITKProcessType.h"
#include "VTKProcessType.h"

class Ui_QWindow;

class Window : public QMainWindow
{
	Q_OBJECT
public:

	Window();
	~Window();

public slots:

	virtual void slotExit();
	virtual void openSingleFile();
	virtual void openFiles();
	virtual void ItemEvent();
	virtual void getInformation();

	virtual void mouseWheelUpEvent(vtkObject*, unsigned long, void*, void*);
	virtual void mouseWheelDownEvent(vtkObject*, unsigned long, void*, void*);

public:

protected:
	
	void readDicomFile();
	void readDicomDir();
	void readDicom2D();
	void readDicom3D();
	void readDicom2DHeader();
	void readDicom3DHeader();

private:

	QString dicomFile;
	QString dicomDir;

	bool canRead;

	dicomDirReaderType::Pointer dicomDirReader;
	dicomFileReaderType::Pointer dicomFileReader;
	vtkSmartPointer<vtkRenderer> renderer;
	GDCMImageType::Pointer dicomIO;

private:

	vtkSmartPointer<vtkEventQtSlotConnect> Connections;

private:
	Ui_QWindow * ui;
};

#endif