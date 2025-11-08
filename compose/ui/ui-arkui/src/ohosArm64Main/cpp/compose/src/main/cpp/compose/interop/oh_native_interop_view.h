//#import "oh_native_interop_wrap_node.h"
//#include <napi/native_api.h>
//
//class InteractionArkUIView {
//private:
//    void* context;
//    PointInsideCallback pointInsideCallback;
//    TouchesEventCallback touchesEventCallback;
//    UpdateTouchesCountCallback updateTouchesCallback;
//    CheckBoundsCallback checkBoundsCallback;
//    KeyboardEventCallback keyboardEventCallback;
//
//    int touchesCount;
//    bool isTouchesConsuming;
//    bool becomeFirstResponder;
//
//public:
//    UIView* view;
//
//    InteractionArkUIView(
//            void* ctx,
//            PointInsideCallback pointInsideCb,
//            TouchesEventCallback touchesEventCb,
//            UpdateTouchesCountCallback updateTouchesCb,
//            CheckBoundsCallback checkBoundsCb,
//            KeyboardEventCallback keyboardEventCb,
//            bool firstResponder
//    ) : context(ctx),
//        pointInsideCallback(pointInsideCb),
//        touchesEventCallback(touchesEventCb),
//        updateTouchesCallback(updateTouchesCb),
//        checkBoundsCallback(checkBoundsCb),
//        keyboardEventCallback(keyboardEventCb),
//        touchesCount(0),
//        isTouchesConsuming(false),
//        becomeFirstResponder(firstResponder) {
//
//        // 创建实际的 ArkUIView
//        view = [[UIView alloc] initWithFrame:CGRectZero];
//        view.multipleTouchEnabled = YES;
//        view.userInteractionEnabled = YES;
//    }
//
//    ~InteractionArkUIView() {
//        if (view) {
//            [view release];
//        }
//    }
//
//    bool canBecomeFirstResponder() {
//        return becomeFirstResponder;
//    }
//
//    void handleTouchesBegan(void* touches, void* event);
//
//    void handleTouchesEnded(void* touches, void* event);
//
//    void handleTouchesMoved(void* touches, void* event);
//
//    void handleTouchesCancelled(void* touches, void* event);
//
//private:
//    void handleOriginalTouchesBegan(void* touches, void* event);
//
//    void handleOriginalTouchesEnded(void* touches, void* event);
//};
