#pragma once

#include <Doom_Core.h>

namespace doom
{
	class AutoRotate : public PlainComponent
	{
	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
