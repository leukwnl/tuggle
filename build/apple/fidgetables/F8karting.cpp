//
//  F8karting.cpp
//  Tuggle
//
//  Implementation of F8karting - a single button toy.
//

#include "F8karting.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance - Orange/Tangerine color scheme
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(255, 140, 0, 255)    // Dark orange
#define BUTTON_COLOR_PRESSED    Color4(225, 110, 0, 255)    // Darker orange
#define BUTTON_COLOR_INACTIVE   Color4(255, 190, 120, 255)  // Dimmed orange

#pragma mark -
#pragma mark Constructors

F8karting::F8karting() : FidgetableView(), _buttonRadius(100.0f) {}

F8karting::~F8karting() {
    dispose();
}

bool F8karting::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F8karting> F8karting::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F8karting> result = std::make_shared<F8karting>();
    if (result->init(8, pageSize)) {
        return result;
    }
    return nullptr;
}

void F8karting::dispose() {
    if (_button != nullptr) {
        _button->deactivate();
        _button->clearListeners();
        _button = nullptr;
    }
    _buttonNode = nullptr;
    FidgetableView::dispose();
}

#pragma mark -
#pragma mark Content Building

void F8karting::buildContent() {
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    _buttonNode = normalNode;
    
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f8karting_button");
    
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F8karting::onPressed() {
    CULog("F8karting pressed");
}

void F8karting::update(float timestep) {
    FidgetableView::update(timestep);
}

void F8karting::setActive(bool active) {
    FidgetableView::setActive(active);
    
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F8karting::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F8karting::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

