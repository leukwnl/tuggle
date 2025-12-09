//
//  F7samba.h
//  Tuggle
//
//  Seventh fidgetable toy - a single interactive button.
//

#ifndef __F7SAMBA_H__
#define __F7SAMBA_H__

#include "FidgetableView.h"

/**
 * Seventh fidgetable toy in the carousel.
 * Currently displays a single circular button.
 */
class F7samba : public FidgetableView {
protected:
    /** The interactive button */
    std::shared_ptr<cugl::scene2::Button> _button;
    
    /** The button's visual node */
    std::shared_ptr<cugl::scene2::PolygonNode> _buttonNode;
    
    /** Button radius */
    float _buttonRadius;
    
    /**
     * Creates the visual content for this fidgetable.
     */
    void buildContent() override;
    
    /**
     * Called when the button is pressed.
     */
    virtual void onPressed();
    
public:
    F7samba();
    virtual ~F7samba();
    
    bool init(int index, const cugl::Size& pageSize) override;
    static std::shared_ptr<F7samba> alloc(const cugl::Size& pageSize);
    void dispose() override;
    void update(float timestep) override;
    void setActive(bool active) override;
    void activateInputs() override;
    void deactivateInputs() override;
};

#endif /* __F7SAMBA_H__ */

