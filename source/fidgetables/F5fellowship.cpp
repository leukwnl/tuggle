//
//  F5fellowship.cpp
//  Tuggle
//
//  Implementation of F5fellowship - a single button toy.
//

#include "F5fellowship.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance - Purple/Violet color scheme
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(147, 112, 219, 255)  // Medium purple
#define BUTTON_COLOR_PRESSED    Color4(117, 82, 189, 255)   // Darker purple
#define BUTTON_COLOR_INACTIVE   Color4(190, 170, 235, 255)  // Dimmed purple

#pragma mark -
#pragma mark Constructors

F5fellowship::F5fellowship() : FidgetableView(), _buttonRadius(100.0f) {}

F5fellowship::~F5fellowship() {
    dispose();
}

bool F5fellowship::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F5fellowship> F5fellowship::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F5fellowship> result = std::make_shared<F5fellowship>();
    if (result->init(5, pageSize)) {
        return result;
    }
    return nullptr;
}

void F5fellowship::dispose() {
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

void F5fellowship::buildContent() {
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    _buttonNode = normalNode;
    
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f5fellowship_button");
    
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F5fellowship::onPressed() {
    CULog("F5fellowship pressed");
}

void F5fellowship::update(float timestep) {
    FidgetableView::update(timestep);
}

void F5fellowship::setActive(bool active) {
    FidgetableView::setActive(active);
    
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F5fellowship::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F5fellowship::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

