//
//  F1tancho.cpp
//  Tuggle
//
//  Implementation of F1tancho - a single button toy.
//

#include "F1tancho.h"

using namespace cugl;
using namespace cugl::scene2;

// Button appearance
#define BUTTON_RADIUS_RATIO 0.25f
#define BUTTON_COLOR_NORMAL     Color4(100, 149, 237, 255)  // Cornflower blue
#define BUTTON_COLOR_PRESSED    Color4(70, 119, 207, 255)   // Darker blue
#define BUTTON_COLOR_INACTIVE   Color4(150, 180, 220, 255)  // Dimmed blue

#pragma mark -
#pragma mark Constructors

F1tancho::F1tancho() : FidgetableView(), _buttonRadius(100.0f) {}

F1tancho::~F1tancho() {
    dispose();
}

bool F1tancho::init(int index, const cugl::Size& pageSize) {
    _buttonRadius = pageSize.width * BUTTON_RADIUS_RATIO;
    return FidgetableView::init(index, pageSize);
}

std::shared_ptr<F1tancho> F1tancho::alloc(const cugl::Size& pageSize) {
    std::shared_ptr<F1tancho> result = std::make_shared<F1tancho>();
    if (result->init(1, pageSize)) {
        return result;
    }
    return nullptr;
}

void F1tancho::dispose() {
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

void F1tancho::buildContent() {
    // Calculate center position
    Vec2 centerPos(_pageSize.width / 2, _pageSize.height / 2 + 50);
    
    // Create button visuals
    auto normalNode = createCircle(_buttonRadius, BUTTON_COLOR_NORMAL);
    auto pressedNode = createCircle(_buttonRadius, BUTTON_COLOR_PRESSED);
    
    // Store reference to normal node for color changes
    _buttonNode = normalNode;
    
    // Create the button
    _button = Button::alloc(normalNode, pressedNode);
    _button->setAnchor(Vec2::ANCHOR_CENTER);
    _button->setPosition(centerPos);
    _button->setName("f1tancho_button");
    
    // Set up listener
    _button->addListener([this](const std::string& name, bool down) {
        if (!down && _isActive) {
            onPressed();
        }
    });
    
    // Add to root node
    _rootNode->addChild(_button);
}

#pragma mark -
#pragma mark Interaction

void F1tancho::onPressed() {
    CULog("F1tancho pressed");
}

void F1tancho::update(float timestep) {
    FidgetableView::update(timestep);
    // Add custom animation here
}

void F1tancho::setActive(bool active) {
    FidgetableView::setActive(active);
    
    // Update button appearance based on active state
    if (_buttonNode != nullptr) {
        if (active) {
            _buttonNode->setColor(BUTTON_COLOR_NORMAL);
        } else {
            _buttonNode->setColor(BUTTON_COLOR_INACTIVE);
        }
    }
}

void F1tancho::activateInputs() {
    if (_button != nullptr) {
        _button->activate();
    }
}

void F1tancho::deactivateInputs() {
    if (_button != nullptr) {
        _button->deactivate();
    }
}

