
/* Frame object interface */

#ifndef Py_FRAMEOBJECT_H
#define Py_FRAMEOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int b_type;			/* what kind of block this is */
    int b_handler;		/* where to jump to find handler */
    int b_level;		/* value stack level to pop to */
} PyTryBlock;

typedef struct _frame {
    PyObject_VAR_HEAD
    
    // 执行环境链上的前一个frame
    struct _frame *f_back;	/* previous frame, or NULL */
    
    // PyCodeObject对象
    PyCodeObject *f_code;	/* code segment */
    
    // builtin名字空间
    PyObject *f_builtins;	/* builtin symbol table (PyDictObject) */
    
    // global名字空间
    PyObject *f_globals;	/* global symbol table (PyDictObject) */
    
    // local名字空间
    PyObject *f_locals;		/* local symbol table (any mapping) */
    
    // 运行时栈的栈底位置
    PyObject **f_valuestack;	/* points after the last local */
    
    // 运行时栈的栈顶位置
    /* Next free slot in f_valuestack.  Frame creation sets to f_valuestack.
       Frame evaluation usually NULLs it, but a frame that yields sets it
       to the current stack top. */
    PyObject **f_stacktop;
    PyObject *f_trace;		/* Trace function */

    /* If an exception is raised in this frame, the next three are used to
     * record the exception info (if any) originally in the thread state.  See
     * comments before set_exc_info() -- it's not obvious.
     * Invariant:  if _type is NULL, then so are _value and _traceback.
     * Desired invariant:  all three are NULL, or all three are non-NULL.  That
     * one isn't currently true, but "should be".
     */
    PyObject *f_exc_type, *f_exc_value, *f_exc_traceback;

    PyThreadState *f_tstate;
    
    // 上一条字节码指令在f_code中偏移位置
    int f_lasti;		/* Last instruction if called */
    
    // 当前字节码对应的源代码行
    /* Call PyFrame_GetLineNumber() instead of reading this field
       directly.  As of 2.3 f_lineno is only valid when tracing is
       active (i.e. when f_trace is set).  At other times we use
       PyCode_Addr2Line to calculate the line from the current
       bytecode index. */
    int f_lineno;		/* Current line number */
    int f_iblock;		/* index in f_blockstack */
    PyTryBlock f_blockstack[CO_MAXBLOCKS]; /* for try and loop blocks */
    
    // 动态内存，维护（局部变量+cell对象集合+free对象集合+运行时栈）所需要的空间
    PyObject *f_localsplus[1];	/* locals+stack, dynamically sized */
} PyFrameObject;


/* Standard object interface */

PyAPI_DATA(PyTypeObject) PyFrame_Type;

#define PyFrame_Check(op) (Py_TYPE(op) == &PyFrame_Type)
#define PyFrame_IsRestricted(f) \
	((f)->f_builtins != (f)->f_tstate->interp->builtins)

PyAPI_FUNC(PyFrameObject *) PyFrame_New(PyThreadState *, PyCodeObject *,
                                       PyObject *, PyObject *);


/* The rest of the interface is specific for frame objects */

/* Block management functions */

PyAPI_FUNC(void) PyFrame_BlockSetup(PyFrameObject *, int, int, int);
PyAPI_FUNC(PyTryBlock *) PyFrame_BlockPop(PyFrameObject *);

/* Extend the value stack */

PyAPI_FUNC(PyObject **) PyFrame_ExtendStack(PyFrameObject *, int, int);

/* Conversions between "fast locals" and locals in dictionary */

PyAPI_FUNC(void) PyFrame_LocalsToFast(PyFrameObject *, int);
PyAPI_FUNC(void) PyFrame_FastToLocals(PyFrameObject *);

PyAPI_FUNC(int) PyFrame_ClearFreeList(void);

/* Return the line of code the frame is currently executing. */
PyAPI_FUNC(int) PyFrame_GetLineNumber(PyFrameObject *);

#ifdef __cplusplus
}
#endif
#endif /* !Py_FRAMEOBJECT_H */
