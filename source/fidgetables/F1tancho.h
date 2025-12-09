//
//  F1tancho.h
//  Tuggle
//
//  First fidgetable toy - a single interactive button.
//

#ifndef __F1TANCHO_H__
#define __F1TANCHO_H__

#include "FidgetableView.h"

/**
 * First fidgetable toy in the carousel.
 * Currently displays a single circular button.
 */
class F1tancho : public FidgetableView {
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
  F1tancho();
  virtual ~F1tancho();

  /**
   * Initializes this fidgetable.
   */
  bool init(int index, const cugl::Size &pageSize) override;

  /**
   * Static allocator for F1tancho.
   */
  static std::shared_ptr<F1tancho> alloc(const cugl::Size &pageSize);

  /**
   * Disposes of all resources.
   */
  void dispose() override;

  /**
   * Updates this fidgetable.
   */
  void update(float timestep) override;

  /**
   * Sets whether this fidgetable is active.
   */
  void setActive(bool active) override;

  /**
   * Activates input listeners.
   */
  void activateInputs() override;

  /**
   * Deactivates input listeners.
   */
  void deactivateInputs() override;
};

#endif /* __F1TANCHO_H__ */

