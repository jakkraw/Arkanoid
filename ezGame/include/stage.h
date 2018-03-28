#pragma once

namespace ezGame {

	struct Ez;

	struct Stage {
		virtual void setup(Ez&) {}
		virtual void cleanup(Ez&){}
		virtual void logic(Ez&) = 0;
		virtual ~Stage() = default;
	};
}