#ifndef CCM_SINGLETON_H_
#define CCM_SINGLETON_H_

#define SINGLETON_DEFINE(type_name)	\
static type_name* GetInstance()	\
{\
    static type_name type_instance;\
    return &type_instance;\
}\
\
type_name (const type_name&) = delete;\
type_name& operator=(const type_name) = delete;\


#endif // !CCM_SINGLETON_H_
