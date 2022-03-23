#pragma once
#include <string>

namespace Countries {

	struct Countries {
		std::string Capital;
		int Population;
	}

	Bulgaria{ "Sofia", 3214212 };
	;

	namespace Areas {
		struct Areas
		{
			std::string Name;
			std::string Mayor;
			int Population;
		}
		
		Burgas{ "Burgas", "Kmetcho", 30000 };
		;
	}
}