#include <Common/Common.hpp>
#include <EXTMR/ExtendedMirror.hpp>
#include <EXTMR/Exceptions/NotFoundExceptions.hpp>

using namespace std;
using namespace extmr;

TypeRegister& TypeRegister::getTypeReg()
{
    static TypeRegister typeReg;
    return typeReg;
}


TypeRegister::TypeRegister()
{
    // register the base types
    registerType<char>();
    registerType<short>();
    registerType<int>();
    registerType<float>();
    registerType<double>();
    registerType<uchar>();
    registerType<ushort>();
    registerType<bool>();
    
    // a void class is needed in the type register and Class::Void cannot be
    // used since it may be still uninitialized
    Class* voidClass = new Class("void");
    typesByName_.insert(voidClass);
    typesById_.insert(voidClass);
    classesByName_.insert(voidClass);
    classesById_.insert(voidClass);
}


const Type& TypeRegister::getType(const string& typeName) const
{
    Type* type = ptrSet::findByKey(typesByName_, typeName);
    if (type)
        return *type;
    else
        throw TypeNotFoundException(typeName);
}


const Type& TypeRegister::getType(const type_info& cppType) const
{
    Type* type = ptrSet::findByKey(typesById_, cppType);
    if (type)
        return *type;
    else
        throw TypeNotFoundException(cppType.name());
}


const Class& TypeRegister::getClass(const string& className) const
{
    Class* clazz = ptrSet::findByKey(classesByName_, className);
    if (clazz)
        return *clazz;
    else
        throw TypeNotFoundException(className);
}


const Class& TypeRegister::getClass(const type_info& cppType) const
{
    Class* clazz = ptrSet::findByKey(classesById_, cppType);
    if (clazz)
        return *clazz;
    else
        throw TypeNotFoundException(cppType.name());
}


const Template& TypeRegister::getTemplate(const string& templateName) const
{
    Template* tempjate = ptrSet::findByKey(templates_, templateName);
    if (tempjate)
        return *tempjate;
    else
        throw TemplateNotFoundException(templateName);
}


const ConstTypeSetById& TypeRegister::getTypes() const
{
    return reinterpret_cast<const ConstTypeSetById&>(typesById_);
}


const ConstClassSetById& TypeRegister::getClasses() const
{
    return reinterpret_cast<const ConstClassSetById&>(classesById_);
}


const ConstTemplateSet& TypeRegister::getTemplates() const
{
    return reinterpret_cast<const ConstTemplateSet&>(templates_);
}