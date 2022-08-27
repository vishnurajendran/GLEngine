#include <GLEngine/AudioSystem/AudioSystem.h>
#include <GLEngine/Debugging.h>

namespace GLengine {
	AudioEngine* AudioSystem::engine;

	bool AudioSystem::AudioSystemInitialised(SoundSource* source) {
		bool res = engine != nullptr;
		bool res2 = source != nullptr;
		if (!res) {
			Debug::LogError("AudioSystem::Audio System not initialised");
		}
		if (!res2) {
			Debug::LogError("AudioSystem::Audio Source not initialised");
		}
		return res && res2;
	}

	bool AudioSystem::AudioSystemInitialised() {
		bool res = engine != nullptr;
		if (!res) {
			Debug::LogError("AudioSystem::Audio System not initialised");
		}

		return res;
	}

	void AudioSystem::Initialise() {
		if (engine == nullptr) {
			irrklang::ISoundDeviceList* deviceList = irrklang::createSoundDeviceList();
			std::string txt = "Audio Devices Available\n";
			for (int i = 0; i < deviceList->getDeviceCount(); ++i)
				txt += "\t" + std::to_string(i) + "->" + deviceList->getDeviceDescription(i) + "\n";
			Debug::LogInfo(txt.c_str());
			const char* deviceID = deviceList->getDeviceID(0);
			engine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_DEFAULT_OPTIONS,deviceID);
			Debug::LogInfo("AudioSystem::Initialised");
		}
	}

	void AudioSystem::Cleanup() {
		if (engine != nullptr)
			engine->drop();

		Debug::LogInfo("AudioSystem::Cleanup");
	}

	void AudioSystem::PlaySource(SoundSource* source, float volume, bool loop) {
		if (AudioSystemInitialised(source)) {
			auto log = "Playing " + std::string(source->getName()) + "( " + std::to_string(source->getPlayLength())
						+ ")_" + " with volume " + std::to_string(volume) + " Looping " + (loop ? "Yes" : "No");
			Debug::Log(log.c_str());
			engine->play2D(source,loop);
		}
	}

	void AudioSystem::StopSource(SoundSource* source) {
		if (AudioSystemInitialised(source))
			engine->stopAllSoundsOfSoundSource(source);
	}

	bool AudioSystem::GetPlayStatus(SoundSource* source) {
		if (AudioSystemInitialised(source))
			return engine->isCurrentlyPlaying(source);
		else
			return false;
	}

	AudioClip* AudioSystem::GetClip(std::string fileName) {
		if (AudioSystemInitialised())
			return new AudioClip(engine->addSoundSourceFromFile(fileName.c_str()));
		else
			return nullptr;
	}
};