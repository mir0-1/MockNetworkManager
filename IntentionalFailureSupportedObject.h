#pragma once

class IntentionalFailureSupportedObject
{
	private:
		bool failOnPurpose;

	public:
		void setFailOnPurpose(bool value);
		bool getFailOnPurpose();
}
