#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmdline/cmdline.h>

#define NANOSVG_IMPLEMENTATION   
#include <nanosvg/nanosvg.h>
#include <iostream>
#include <sstream>

//#include "stdafx.h"
//#include <string>
//#include <cstdio>

//#include <tinyxml2/tinyxml2.h>

typedef float real;
typedef glm::vec3 vec3;
typedef glm::vec2 vec2;
#define REAL float

struct AABB {

	AABB()
		: mMin(std::numeric_limits<real>::max()),
		mMax(-std::numeric_limits<real>::max())
	{}

	AABB(const vec2& mi, const vec2& ma) : mMin(mi), mMax(ma) {
		////
	}

	void offset(const vec2& o) {
		mMin += o;
		mMax += o;
	}

	void add(const vec2 &p) {
		mMin = glm::min(p, mMin);
		mMax = glm::max(p, mMax);
	}

	vec2 len() const { return mMax - mMin; }

	vec2 mMin;
	vec2 mMax;
};


int main(int ac, char** av) {
	//for (int i = 1; i < ac; ++i) {
		// remove layer generated by Illustrator, these layers are normally hidden in the CSS style, but nanosvg does not handle that.
		//{
		//	tinyxml2::XMLDocument doc;
		//	doc.LoadFile(av[i]);
		//	auto svgElement = doc.FirstChildElement("svg");
		//	if (svgElement) {
		//		auto gElement = svgElement->FirstChildElement("g");
		//		while (gElement) {
		//			bool removeElement = false;
		//			for (auto attr = gElement->FirstAttribute(); attr && !removeElement; attr = attr->Next()) {
		//				if (strcmp(attr->Name(), "id") == 0) {
		//					removeElement = strstr(attr->Value(), "Layer_") != NULL;
		//				}
		//				
		//			}
		//			auto pElement = gElement;					
		//			gElement = gElement->NextSiblingElement("g");
		//			if (removeElement) {
		//				svgElement->DeleteChild(pElement);
		//			}
		//		}
		//		doc.SaveFile(av[i], true);
		//	}
		//}

		//{
			struct NSVGimage* image;
			image = nsvgParse(av[1], "px", 1);
			if (image) {
				AABB aabb;
				aabb.add(glm::vec2(image->realBounds[0], image->realBounds[1]));
				aabb.add(glm::vec2(image->realBounds[2], image->realBounds[3]));

				glm::vec2 len = aabb.len();

				//tinyxml2::XMLDocument doc;
				//doc.Parse(av[1]);
				//auto svgElement = doc.FirstChildElement("svg");
				
				//if (svgElement) {
					std::stringstream ss;
					ss << aabb.mMin.x << " " << aabb.mMin.y << " " << len.x << " " << len.y;
					std::cout << ss.str().c_str() << std::endl;
					//std::cout.flush();
					//svgElement->SetAttribute("viewBox", ss.str().c_str());
				//}
				//doc.SaveFile(av[i], true);
				//doc.Print();
				nsvgDelete(image);
			}
		//}
	//}
	return 0;
}
