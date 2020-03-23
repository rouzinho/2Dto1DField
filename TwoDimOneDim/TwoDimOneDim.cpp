/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        EarSubscriber.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "TwoDimOneDim.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include <cmath>
#include <iostream>

using namespace std;





// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
TwoDimOneDim::TwoDimOneDim()
:
cedar::proc::Step(true),
mOutput(new cedar::aux::MatData(cv::Mat::zeros(1, 100, CV_32F))),
mInputX(new cedar::aux::MatData(cv::Mat::zeros(10, 10, CV_32F)))
{
this->declareInput("2D", true);
this->declareOutput("1D",mOutput);

valPeak = 0;

}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
//
void TwoDimOneDim::compute(const cedar::proc::Arguments&)
{

  cv::Mat& field = mInputX->getData();
  cedar::aux::ConstDataPtr opX = this->getInputSlot("2D")->getData();
  field = opX->getData<cv::Mat>();

  cv::Size s = field.size();
  int size_onedim = s.height * s.width;

  cv::Mat output = cv::Mat::zeros(size_onedim, 1,CV_32F);

  maxX = 0;
  maxY = 0;
  minX = s.width;
  minY = s.height;

  for(int i = 0;i < s.height;i++)
  {
    for(int j = 0;j < s.width;j++)
    {
      valPeak = field.at<float>(i,j);
      if(valPeak > 0.9)
      {
        if(j < minX)
        {
          minX = j;
        }
        if(i < minY)
        {
          minY = i;
        }
        if(j > maxX)
        {
          maxX = j;
        }
        if(i > maxY)
        {
          maxY = i;
        }
      }
    }
  }

  posX = (static_cast<double>(minX) + static_cast<double>(maxX))/2;
  posY = (static_cast<double>(minY) + static_cast<double>(maxY))/2;

  int x = static_cast<int>(posX);
  int y = static_cast<int>(posY);

  int new_pos = (y * s.height) + x;

  output.at<float>(new_pos,0) = 2.0;

  this->mOutput->setData(output);

}

void TwoDimOneDim::reCompute()
{

}

void TwoDimOneDim::reName()
{

}

void TwoDimOneDim::reset()
{

	//ros::shutdown();

}
