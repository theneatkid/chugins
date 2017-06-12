//-----------------------------------------------------------------------------
// Entaro ChucK Developer!
// This is a Chugin boilerplate, generated by chuginate!
//-----------------------------------------------------------------------------

// this should align with the correct versions of these ChucK files
#include "chuck_dl.h"
#include "chuck_def.h"

// general includes
#include <stdio.h>
#include <limits.h>

// declaration of chugin constructor
CK_DLL_CTOR(%(CHUGIN_LCNAME)%_ctor);
// declaration of chugin desctructor
CK_DLL_DTOR(%(CHUGIN_LCNAME)%_dtor);

// example of getter/setter
CK_DLL_MFUN(%(CHUGIN_LCNAME)%_setParam);
CK_DLL_MFUN(%(CHUGIN_LCNAME)%_getParam);

// for Chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICK(%(CHUGIN_LCNAME)%_tick);

// this is a special offset reserved for Chugin internal data
t_CKINT %(CHUGIN_LCNAME)%_data_offset = 0;


// class definition for internal Chugin data
// (note: this isn't strictly necessary, but serves as example
// of one recommended approach)
class %(CHUGIN_NAME)%
{
public:
    // constructor
    %(CHUGIN_NAME)%( t_CKFLOAT fs)
    {
        m_param = 0;
    }

    // for Chugins extending UGen
    SAMPLE tick( SAMPLE in )
    {
        // default: this passes whatever input is patched into Chugin
        return in;
    }

    // set parameter example
    t_CKFLOAT setParam( t_CKFLOAT p )
    {
        m_param = p;
        return p;
    }

    // get parameter example
    t_CKFLOAT getParam() { return m_param; }
    
private:
    // instance data
    t_CKFLOAT m_param;
};


// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( %(CHUGIN_NAME)% )
{
    // hmm, don't change this...
    QUERY->setname(QUERY, "%(CHUGIN_NAME)%");
    
    // begin the class definition
    // can change the second argument to extend a different ChucK class
    QUERY->begin_class(QUERY, "%(CHUGIN_NAME)%", "UGen");

    // register the constructor (probably no need to change)
    QUERY->add_ctor(QUERY, %(CHUGIN_LCNAME)%_ctor);
    // register the destructor (probably no need to change)
    QUERY->add_dtor(QUERY, %(CHUGIN_LCNAME)%_dtor);
    
    // for UGen's only: add tick function
    QUERY->add_ugen_func(QUERY, %(CHUGIN_LCNAME)%_tick, NULL, 1, 1);
    
    // NOTE: if this is to be a UGen with more than 1 channel, 
    // e.g., a multichannel UGen -- will need to use add_ugen_funcf()
    // and declare a tickf function using CK_DLL_TICKF

    // example of adding setter method
    QUERY->add_mfun(QUERY, %(CHUGIN_LCNAME)%_setParam, "float", "param");
    // example of adding argument to the above method
    QUERY->add_arg(QUERY, "float", "arg");

    // example of adding getter method
    QUERY->add_mfun(QUERY, %(CHUGIN_LCNAME)%_getParam, "float", "param");
    
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    %(CHUGIN_LCNAME)%_data_offset = QUERY->add_mvar(QUERY, "int", "@%(CHUGIN_INITIALS)%_data", false);

    // end the class definition
    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);

    // wasn't that a breeze?
    return TRUE;
}


// implementation for the constructor
CK_DLL_CTOR(%(CHUGIN_LCNAME)%_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, %(CHUGIN_LCNAME)%_data_offset) = 0;
    
    // instantiate our internal c++ class representation
    %(CHUGIN_NAME)% * %(CHUGIN_INITIALS)%_obj = new %(CHUGIN_NAME)%(API->vm->get_srate( API ));
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, %(CHUGIN_LCNAME)%_data_offset) = (t_CKINT) %(CHUGIN_INITIALS)%_obj;
}


// implementation for the destructor
CK_DLL_DTOR(%(CHUGIN_LCNAME)%_dtor)
{
    // get our c++ class pointer
    %(CHUGIN_NAME)% * %(CHUGIN_INITIALS)%_obj = (%(CHUGIN_NAME)% *) OBJ_MEMBER_INT(SELF, %(CHUGIN_LCNAME)%_data_offset);
    // check it
    if( %(CHUGIN_INITIALS)%_obj )
    {
        // clean up
        delete %(CHUGIN_INITIALS)%_obj;
        OBJ_MEMBER_INT(SELF, %(CHUGIN_LCNAME)%_data_offset) = 0;
        %(CHUGIN_INITIALS)%_obj = NULL;
    }
}


// implementation for tick function
CK_DLL_TICK(%(CHUGIN_LCNAME)%_tick)
{
    // get our c++ class pointer
    %(CHUGIN_NAME)% * %(CHUGIN_INITIALS)%_obj = (%(CHUGIN_NAME)% *) OBJ_MEMBER_INT(SELF, %(CHUGIN_LCNAME)%_data_offset);
 
    // invoke our tick function; store in the magical out variable
    if(%(CHUGIN_INITIALS)%_obj) *out = %(CHUGIN_INITIALS)%_obj->tick(in);

    // yes
    return TRUE;
}


// example implementation for setter
CK_DLL_MFUN(%(CHUGIN_LCNAME)%_setParam)
{
    // get our c++ class pointer
    %(CHUGIN_NAME)% * %(CHUGIN_INITIALS)%_obj = (%(CHUGIN_NAME)% *) OBJ_MEMBER_INT(SELF, %(CHUGIN_LCNAME)%_data_offset);
    // set the return value
    RETURN->v_float = %(CHUGIN_INITIALS)%_obj->setParam(GET_NEXT_FLOAT(ARGS));
}


// example implementation for getter
CK_DLL_MFUN(%(CHUGIN_LCNAME)%_getParam)
{
    // get our c++ class pointer
    %(CHUGIN_NAME)% * %(CHUGIN_INITIALS)%_obj = (%(CHUGIN_NAME)% *) OBJ_MEMBER_INT(SELF, %(CHUGIN_LCNAME)%_data_offset);
    // set the return value
    RETURN->v_float = %(CHUGIN_INITIALS)%_obj->getParam();
}
