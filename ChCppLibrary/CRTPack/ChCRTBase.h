#ifndef Ch_CRT_Base
#define Ch_CRT_Base

#ifdef CRT
#ifndef Ch_CRT_Operator_Functions_To_Base
#define Ch_CRT_Operator_Functions_To_Base(_BaseClass)\
_BaseClass##& operator =(const _BaseClass##& _val) { if(this != &_val)value->pack = _val.value->pack; return *this; }
#endif
#else
#ifndef Ch_CRT_Operator_Functions_To_Base
#define Ch_CRT_Operator_Functions_To_Base(_BaseClass)
#endif
#endif

#ifdef CRT
#ifndef Ch_CRT_Operator_Functions_To_Pack
#define Ch_CRT_Operator_Functions_To_Pack(_BaseClass,_PackClass)\
_BaseClass##& operator =(const _PackClass##& _val) { if(&value->pack != &_val)value->pack = _val; return *this; }\
operator _PackClass##& () { return value->pack; }
#endif
#else
#ifndef Ch_CRT_Operator_Functions_To_Pack
#define Ch_CRT_Operator_Functions_To_Pack(_BaseClass,_PackClass)
#endif
#endif

#ifdef CRT
#ifndef Ch_CRT_ConstructorDestructor_Functions
#define Ch_CRT_ConstructorDestructor_Functions(_BaseClass,_PackClass)\
_BaseClass##(const _PackClass& _val) {\
	value = new _BaseClass##CRT();\
	if (&_val != &value->pack)value->pack = _val; };
#endif
#else
#ifndef Ch_CRT_ConstructorDestructor_Functions
#define Ch_CRT_ConstructorDestructor_Functions(_BaseClass,_PackClass)
#endif
#endif

#endif