#pragma once

#ifndef INC_ERRCODES_H
#define INC_ERRCODES_H


enum ErrCode
{
	err_noErr = 0,
	err_cantRecreateRenderDevice,
	err_cantBeginScene,
	err_cantEndScene,
	err_cantRecreateInputMan,
	err_cantSetTexturesDir,
	err_cantAddTexture,
	err_cantSetCursor,
	err_cantDrawCursor,
	err_cantUnloadResources,
	err_cantLoadResources,
	err_cantReloadSprite,
	err_cantDrawScene,
	err_cantBeginSprite,
	err_cantEndSprite,
	err_cantUnloadMap,
	err_cantLoadScene,
	err_cantUnloadScene,
	err_cantLoadMap,
	err_cantDrawBackground,
	err_cantLoadBackground,
	err_cantDrawThing,
	err_cantDrawGui,
	err_cantLoadGui,
	err_invalidObjsFile,
	err_cantGetTi,
	err_cantInitResources,
	err_cantDisposeResources,
	err_guiInputError,
	err_unknownGuiMode,
	err_cantParseGridItemToPrototype,
	err_cantFindRequiredBasement,
	err_unknownRequirements,
	err_cantGetFileVersion,
	err_cantSaveMapToFile,
	err_cantLoadMapFromFile,
	err_realThingHasNoParent,
	err_cantLoadThing,
	err_cantUnloadThing,
	err_cantParseAnimation,

	err_end
};


#endif // INC_ERRCODES_H
