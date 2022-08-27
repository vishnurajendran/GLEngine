#pragma once
#include <GLEngine/Core/Component.h>
#include <irrKlang/irrKlang.h>
#include <glm/glm.hpp>
#include <string>

namespace GLengine {
	typedef irrklang::ISoundEngine AudioEngine;
	typedef irrklang::ISoundSource SoundSource;
	

	//AudioSystem class is not exposed to GLengine applications, it is an internal class,
	//used to play audio streams
	class GLENGINE_API AudioClip; //forwad declaration
	class AudioSystem {
	private:
		static AudioEngine* engine;
	public:
		static void Initialise();
		static void Cleanup();
		static void PlaySource(SoundSource* source, float volume, bool loop);
		static void StopSource(SoundSource* source);
		static bool GetPlayStatus(SoundSource* source);
		static AudioClip* GetClip(std::string fileName);
		static bool AudioSystemInitialised(SoundSource* source);
		static bool AudioSystemInitialised();
	};

	//Audio Clip stores the sound source that contains the audio stream which,
	//can be played by the audio source component
	class GLENGINE_API AudioSource; //forwad declaration
	class GLENGINE_API AudioClip {
	private:
		friend class AudioSource;
		SoundSource* source;
	public:
		inline AudioClip(SoundSource* source) { this->source = source; };
		inline ~AudioClip() { if (source != nullptr) source->drop(); };
		inline std::string GetName() { return source->getName(); };
		inline double GetClipLengthInSeconds() { return source->getPlayLength() / 1000; }; //getPlayLength returns in milliseconds
	};

	//Component that is attached to a GameObject to play sounds in the application
	class GLENGINE_API AudioSource : public IComponent {
	private:
		friend class AudioClip;

		float volume = 1.0f;
		bool loop = true;
		AudioClip* clip;
	public:
		inline void SetClip(AudioClip* clip) { this->clip = clip; };
		inline void Play() { AudioSystem::PlaySource(clip->source, volume, loop); };
		inline void Stop() { AudioSystem::StopSource(clip->source); };
		inline bool IsPlaying() { return AudioSystem::GetPlayStatus(clip->source); };

		inline bool IsLooping() { return loop; };
		inline float GetVolume() { return volume; };
		inline void SetVolume(float volume) { 
			this->volume = glm::clamp(volume,0.0f,1.0f); 
			if (clip != nullptr)
				clip->source->setDefaultVolume(volume);
		};
		inline void SetLoop(bool loop) { this->loop = loop; };
	};
};