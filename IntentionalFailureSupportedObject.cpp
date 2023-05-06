#include "IntentionalFailureSupportedObject.h"

void IntentionalFailureSupportedObject::setFailOnPurpose(bool value)
{
	failOnPurpose = value;
}

bool IntentionalFailureSupportedObject::getFailOnPurpose()
{
	return failOnPurpose;
}
