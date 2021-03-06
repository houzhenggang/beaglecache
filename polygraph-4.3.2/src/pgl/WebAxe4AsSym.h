
/* Web Polygraph       http://www.web-polygraph.org/
 * Copyright 2003-2011 The Measurement Factory
 * Licensed under the Apache License, Version 2.0 */

#ifndef POLYGRAPH__PGL_WEBAXE4ASSYM_H
#define POLYGRAPH__PGL_WEBAXE4ASSYM_H

#include "pgl/VerFourAsSym.h"

// WebAxe-4 addressing scheme
class WebAxe4AsSym: public VerFourAsSym {
	public:
		static const String TheType;

	public:
		WebAxe4AsSym();
		WebAxe4AsSym(const String &aType, PglRec *aRec);

		virtual bool isA(const String &type) const;

	protected:
		virtual SynSym *dupe(const String &dType) const;

		virtual String robots(ArraySym *&addrs) const;
		virtual String servers(ArraySym *&addrs) const;
		virtual String proxies(ArraySym *&addrs) const;
};

#endif
