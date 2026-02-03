#pragma once
#include "resource_holder.hpp"
#include "resource_identifiers.hpp"

#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

#include "music_themes.hpp"

class MusicPlayer
{
public:
	MusicPlayer();

	void Play(MusicThemes theme);
	void Stop();

	void SetPaused(bool paused);
	void SetVolume(float volume);


private:
	sf::Music m_music;
	std::map<MusicThemes, std::string>	m_filenames;
	float m_volume;
};

