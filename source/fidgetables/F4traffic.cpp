//
//  F4traffic.cpp
//  Tuggle
//
//  Implementation of F4traffic - a single button toy.
//

#include "F4traffic.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance - Gold/Amber color scheme
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(255, 193, 37, 255)   // Golden yellow
#define BUTTON_COLOR_PRESSED    Color4(225, 163, 7, 255)    // Darker gold
#define BUTTON_COLOR_INACTIVE   Color4(255, 220, 130, 255)  // Dimmed gold

#pragma mark -
#pragma mark Constructors

F4traffic::F4traffic() : FidgetableView(), _buttonRadius(100.0f) {}

F4traffic::~F4traffic() {
    dispose();
}

bool F4traffic::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F4traffic> F4traffic::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F4traffic> result = std::make_shared<F4traffic>();
    if (result->init(4, pageSize)) {
        return result;
    }
    return nullptr;
}

void F4traffic::dispose() {
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

void F4traffic::buildContent() {
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    _buttonNode = normalNode;
    
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f4traffic_button");
    
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F4traffic::onPressed() {
    CULog("F4traffic pressed");
}

void F4traffic::update(float timestep) {
    FidgetableView::update(timestep);
}

void F4traffic::setActive(bool active) {
    FidgetableView::setActive(active);
    
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F4traffic::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F4traffic::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

