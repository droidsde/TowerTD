
#ifndef __Dota_Legend__RightMenuLayerLayer__
#define __Dota_Legend__RightMenuLayerLayer__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
class RightMenuLayerLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(RightMenuLayerLayer);
	void callback(Ref *sender);
};

#endif /* defined(__Dota_Legend__RightMenuLayerLayer__) */
