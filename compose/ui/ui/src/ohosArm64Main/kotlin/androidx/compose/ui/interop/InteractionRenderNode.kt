//package androidx.compose.ui.interop
//
//import androidx.compose.ui.input.pointer.PointerEventType
//import kotlinx.cinterop.*
//import platform.arkui.*
//
//internal class InteractionArkUIView(
//    private val keyboardEventHandler: KeyboardEventHandler,
//    private var touchesDelegate: Delegate,
//    private val updateTouchesCount: (Int) -> Unit,
//    private val checkBounds: (DpOffset) -> Boolean,
//    private val becomeFirstResponder: Boolean = true,
//) {
//
//    interface Delegate {
//        fun pointInside(point: DpOffset, event: COpaquePointer?): HitTestViewType
//        fun onTouchesEvent(view: COpaquePointer, event: COpaquePointer, phase: UITouchesEventPhase)
//    }
//
//    enum class HitTestViewType {
//        NATIVEVIEW, COMPOSEVIEW, NONE
//    }
//
//    data class DpOffset(val x: Double, val y: Double)
//
//    private var _touchesCount = 0
//        set(value) {
//            field = value
//            updateTouchesCount(value)
//        }
//
//    private var nativeHandle: COpaquePointer? = null
//    private val context = StableRef.create(this)
//    private var isTouchesConsuming: Boolean = false
//
//    init {
//        nativeHandle = createInteractionArkUIView(
//            context = context.asCPointer(),
//            pointInsideCallback = staticCFunction { context, x, y, event ->
//                val wrapper = context?.asStableRef<InteractionArkUIView>()?.get()
//                wrapper?.handlePointInside(x, y, event) ?: HitTestViewType.NONE.ordinal
//            },
//            touchesEventCallback = staticCFunction { context, view, event, phase ->
//                val wrapper = context?.asStableRef<InteractionArkUIView>()?.get()
//                wrapper?.handleTouchesEvent(view, event, phase)
//            },
//            updateTouchesCallback = staticCFunction { context, count ->
//                val wrapper = context?.asStableRef<InteractionArkUIView>()?.get()
//                wrapper?.handleUpdateTouchesCount(count)
//            },
//            checkBoundsCallback = staticCFunction { context, point ->
//                val wrapper = context?.asStableRef<InteractionArkUIView>()?.get()
//                wrapper?.handleCheckBounds(point) ?: false
//            },
//            keyboardEventCallback = staticCFunction { context, event ->
//                val wrapper = context?.asStableRef<InteractionArkUIView>()?.get()
//                wrapper?.handleKeyboardEvent(event)
//            },
//            becomeFirstResponder = becomeFirstResponder,
//        )
//    }
//
//    fun getUIView(): COpaquePointer? {
//        return nativeHandle?.let {
//            getUIViewFromHandle(it)
//        }
//    }
//
//    private fun handlePointInside(x: Double, y: Double, event: COpaquePointer?): Int {
//        val point = DpOffset(x, y)
//        return touchesDelegate.pointInside(point, event).ordinal
//    }
//
//    private fun handleTouchesEvent(view: COpaquePointer, event: COpaquePointer, phase: Int) {
//         when (phase) {
//            0 -> consumeTouchesOnce { originalTouchesBegan(view, event) }
//            1 -> consumeTouchesOnce { originalTouchesEnded(view, event) }
//            2 -> consumeTouchesOnce { originalTouchesMoved(view, event) }
//            3 -> consumeTouchesOnce { originalTouchesCancelled(view, event) }
//            else -> {}
//        }
//    }
//
//    private fun handleUpdateTouchesCount(count: Int) {
//        updateTouchesCount(count)
//    }
//
//    private fun handleCheckBounds(point: CValue<DpOffset>): Boolean {
//        return checkBounds(point.readValue())
//    }
//
//    private fun handleKeyboardEvent(event: COpaquePointer) {
//        // 转换并处理键盘事件
//        keyboardEventHandler.onKeyboardEvent(convertToSkikoKeyboardEvent(event))
//    }
//
//    /**
//     * Wrap onTouchesEvent in this function to avoid calling it recursively.
//     */
//    private inline fun consumeTouchesOnce(block: () -> Unit) {
//        if (isTouchesConsuming) return
//        isTouchesConsuming = true
//        block()
//        isTouchesConsuming = false
//    }
//
//    private fun originalTouchesBegan(touches: Set<*>, withEvent: COpaquePointer?) {
//        _touchesCount += touches.size
//        withEvent?.let { event ->
//            touchesDelegate.onTouchesEvent(this, event, UITouchesEventPhase.BEGAN)
//        }
//    }
//    private fun originalTouchesEnded(touches: Set<*>, withEvent: COpaquePointer?) {
//        _touchesCount -= touches.size
//        withEvent?.let { event ->
//            touchesDelegate.onTouchesEvent(this, event, UITouchesEventPhase.ENDED)
//        }
//    }
//    private fun originalTouchesMoved(touches: Set<*>, withEvent: COpaquePointer?) {
//        withEvent?.let { event ->
//            touchesDelegate.onTouchesEvent(this, event, UITouchesEventPhase.MOVED)
//        }
//    }
//
//    private fun originalTouchesCancelled(touches: Set<*>, withEvent: COpaquePointer?) {
//        _touchesCount -= touches.size
//        withEvent?.let { event ->
//            touchesDelegate.onTouchesEvent(it, event, UITouchesEventPhase.CANCELLED)
//        }
//    }
//
//    fun dispose() {
//        // 清理资源
//        nativeHandle?.let {
//            disposeInteractionArkUIView(it)
//            destroyInteractionArkUIView(it)
//            nativeHandle = null
//        }
//        context.dispose()
//
//        // 清空回调引用
//        touchesDelegate = object : Delegate {
//            override fun pointInside(point: DpOffset, event: COpaquePointer?): HitTestViewType =
//                HitTestViewType.NONE
//            override fun onTouchesEvent(view: COpaquePointer, event: COpaquePointer, phase: UITouchesEventPhase) {}
//        }
//    }
//
//    // 辅助转换函数
//    private fun convertToSkikoKeyboardEvent(event: COpaquePointer): SkikoKeyboardEvent {
//        // 实现键盘事件转换逻辑
//        TODO("Implement keyboard event conversion")
//    }
//
//    private external fun createInteractionArkUIView(
//        context: COpaquePointer,
//        pointInsideCallback: CPointer<CFunction<PointInsideCallback>>,
//        touchesEventCallback: CPointer<CFunction<TouchesEventCallback>>,
//        updateTouchesCallback: CPointer<CFunction<UpdateTouchesCountCallback>>,
//        checkBoundsCallback: CPointer<CFunction<CheckBoundsCallback>>,
//        keyboardEventCallback: CPointer<CFunction<KeyboardEventCallback>>,
//        becomeFirstResponder: Boolean
//    ): COpaquePointer
//
//    private external fun destroyInteractionArkUIView(handle: COpaquePointer)
//    private external fun disposeInteractionArkUIView(handle: COpaquePointer)
//    private external fun touchesBegan(handle: COpaquePointer, touches: COpaquePointer, event: COpaquePointer)
//    private external fun touchesEnded(handle: COpaquePointer, touches: COpaquePointer, event: COpaquePointer)
//    private external fun touchesMoved(handle: COpaquePointer, touches: COpaquePointer, event: COpaquePointer)
//    private external fun touchesCancelled(handle: COpaquePointer, touches: COpaquePointer, event: COpaquePointer)
//    private external fun getUIViewFromHandle(handle: COpaquePointer): COpaquePointer
//
//    // C 回调类型定义
//    private typealias PointInsideCallback = (context: COpaquePointer?, x: Double, y: Double, event: COpaquePointer?) -> Int
//    private typealias TouchesEventCallback = (context: COpaquePointer?, view: COpaquePointer, event: COpaquePointer, phase: Int) -> Unit
//    private typealias UpdateTouchesCountCallback = (context: COpaquePointer?, count: Int) -> Unit
//    private typealias CheckBoundsCallback = (context: COpaquePointer?, point: CValue<DpOffset>) -> Boolean
//    private typealias KeyboardEventCallback = (context: COpaquePointer?, event: COpaquePointer) -> Unit
//}