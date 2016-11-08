#include "stdafx.h"
#include "Engine.h"


ErrCode Engine::Mainloop()
{
	LOG("Engine::Mainloop()");
	ErrCode err = err_noErr;
	ErrCode3d err3d;


	// Start the game
	err = m_game.Start(m_scene);
	if (err != err_noErr)
	{
		echo("ERROR: Can't start the game.");
		Dispose();
		return err;
	}

	Timer timer;
	timer.Start();
	float deltaTime = 0;

	m_isRun = true;
	while (m_isRun && m_game.IsRun())
	{
		if (Doh3d::WinPeekExit())
			break;

		deltaTime = (float)timer.Restart();

		// RenderMan

		if (!Doh3d::RenderMan::IsCreated())
		{
			err = OnRenderDeviceReset();
			if (err != err_noErr)
			{
				echo("ERROR: Can't reset render device.");
				break;
			}
			continue;
		}

		// InputMan

		err3d = Doh3d::InputMan::CheckDevices();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't check input devices.");
			break;
		}

		// Scene update

		err = m_scene.Update(deltaTime);
		if (err != err_noErr)
		{
			echo("ERROR: Can't update scene.");
			break;
		}

		// Scene drawing

		err = m_scene.Draw(m_sprite);
		if (err != err_noErr)
		{
			echo("ERROR: Can't draw scene.");
			break;
		}

		// tmp
		Sleep(10);
	}

	return err;
}
