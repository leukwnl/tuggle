//
//  F4traffic.h
//  Tuggle
//
//  Fourth fidgetable toy - a single interactive button.
//

#ifndef __F4TRAFFIC_H__
#define __F4TRAFFIC_H__

#include "FidgetableView.h"

/**
 * Fourth fidgetable toy in the carousel.
 * Currently displays a single circular button.
 */
class F4traffic : public FidgetableView {
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
    F4traffic();
    virtual ~F4traffic();
    
    bool init(int index, const cugl::Size& pageSize) override;
    static std::shared_ptr<F4traffic> alloc(const cugl::Size& pageSize);
    void dispose() override;
    void update(float timestep) override;
    void setActive(bool active) override;
    void activateInputs() override;
    void deactivateInputs() override;
};

#endif /* __F4TRAFFIC_H__ */

