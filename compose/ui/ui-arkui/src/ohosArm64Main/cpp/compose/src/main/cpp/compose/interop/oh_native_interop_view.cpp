//#import "oh_native_interop_view.h"
//#import <UIKit/UIKit.h>
//
//namespace OH {
//    void InteractionArkUIView::handleTouchesBegan(void* touches, void* event) {
//        if (!ComposeTabService_composeGestureEnable()) {
//            handleOriginalTouchesBegan(touches, event);
//            return;
//        }
//
//        if (isTouchesConsuming) return;
//        isTouchesConsuming = true;
//
//        NSSet* touchSet = (NSSet*)touches;
//        touchesCount += touchSet.count;
//
//        if (updateTouchesCallback) {
//            updateTouchesCallback(context, touchesCount);
//        }
//
//        if (touchesEventCallback && event) {
//            touchesEventCallback(context, (__bridge void*)view, event, 0); // 0 = BEGAN
//        }
//
//        isTouchesConsuming = false;
//    }
//
//    void InteractionArkUIView::handleTouchesEnded(void* touches, void* event) {
//        if (!ComposeTabService_composeGestureEnable()) {
//            handleOriginalTouchesEnded(touches, event);
//            return;
//        }
//
//        if (isTouchesConsuming) return;
//        isTouchesConsuming = true;
//
//        NSSet* touchSet = (NSSet*)touches;
//        touchesCount -= touchSet.count;
//
//        if (updateTouchesCallback) {
//            updateTouchesCallback(context, touchesCount);
//        }
//
//        if (touchesEventCallback && event) {
//            touchesEventCallback(context, (__bridge void*)view, event, 1); // 1 = ENDED
//        }
//
//        isTouchesConsuming = false;
//    }
//
//    void InteractionArkUIView::handleTouchesMoved(void* touches, void* event) {
//    }
//
//    void InteractionArkUIView::handleTouchesCancelled(void* touches, void* event) {
//    }
//
//
//    void InteractionArkUIView::handleOriginalTouchesBegan(void* touches, void* event) {
//        NSSet* touchSet = (NSSet*)touches;
//        touchesCount += touchSet.count;
//
//        if (updateTouchesCallback) {
//            updateTouchesCallback(context, touchesCount);
//        }
//
//        if (touchesEventCallback && event) {
//            touchesEventCallback(context, (__bridge void*)view, event, 0); // 0 = BEGAN
//        }
//    }
//
//    void InteractionArkUIView::handleOriginalTouchesEnded(void* touches, void* event) {
//        // ... 类似的实现
//    }
//}