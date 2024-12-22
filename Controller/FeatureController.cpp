/*
* FeatureController.cpp
* Author: Trung La
* Date: 2024-12-22
* Description: This file contains the implementation for the feature controller.
*/

#include "FeatureController.h"
#include "SideBarModel.h"

FeatureController::FeatureController(QObject *parent)
    : QObject(parent)
    , m_sideBarModel(std::make_unique<SideBarModel>(this))
{
}

FeatureController::~FeatureController()
{
}
