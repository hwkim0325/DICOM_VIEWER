#ifndef IMAGE_TYPE_H
#define IMAGE_TYPE_H

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageSeriesReader.h>
#include <itkMetaDataDictionary.h>
#include <itkMetaDataObject.h>
#include <itkAffineTransform.h>
#include <itkNearestNeighborInterpolateImageFunction.h>

// Filter
#include <itkMinimumMaximumImageFilter.h>
#include <itkShiftScaleImageFilter.h>
#include <itkIntensityWindowingImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkResampleImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkImageToVTKImageFilter.h>

using CharImageType = char;
using UCharImageType = unsigned char;
using ShortPixelType = short;
using UShortPixelType = unsigned short;
using FloatPixelType = float;
using DoublePixelType = double;
using LongDoublePixelType = long double;

constexpr int Dimension_1D = 1;
constexpr int Dimension_2D = 2;
constexpr int Dimension_3D = 3;
constexpr int Dimension_4D = 4;

using Short2DImageType = itk::Image<ShortPixelType, Dimension_2D>;
using Short3DImageType = itk::Image<ShortPixelType, Dimension_3D>;
using Float2DImageType = itk::Image<FloatPixelType, Dimension_2D>;
using Float3DImageType = itk::Image<FloatPixelType, Dimension_3D>;

using dicomFileReaderType = itk::ImageFileReader<Short2DImageType>;
using dicomDirReaderType = itk::ImageSeriesReader<Short3DImageType>;
using GDCMImageType = itk::GDCMImageIO;

using NamesGeneratorType = itk::GDCMSeriesFileNames;
using SeriesIdContainer = std::vector<std::string>;
using FileNamesContainer = std::vector<std::string>;
using DictionaryType = itk::MetaDataDictionary;
using MetaDataStringType = itk::MetaDataObject<std::string>;


using minimumMaximumType = itk::MinimumMaximumImageFilter<Short2DImageType>;

using ShiftScaleType = itk::ShiftScaleImageFilter<Short2DImageType,Short2DImageType>;
using IntensityWindowingImageFilterType = itk::IntensityWindowingImageFilter<Short2DImageType, Short2DImageType>;

using RescaleFilterType2D = itk::RescaleIntensityImageFilter<Short2DImageType, Short2DImageType>;
using RescaleFilterType3D = itk::RescaleIntensityImageFilter<Short3DImageType, Short3DImageType>;

using ResampleFilterType = itk::ResampleImageFilter<Short2DImageType, Short2DImageType>;
using TransformType = itk::AffineTransform<double, Dimension_2D>;
using InterpolatorType = itk::NearestNeighborInterpolateImageFunction<Short2DImageType, double>;

using CastingFilterType2D = itk::CastImageFilter<Short2DImageType, Short2DImageType>;
using CastingFilterType3D = itk::CastImageFilter<Short3DImageType, Short3DImageType>;

using ConvertFilterType2D = itk::ImageToVTKImageFilter<Short2DImageType>;
using ConvertFilterType3D = itk::ImageToVTKImageFilter<Short3DImageType>;

#endif