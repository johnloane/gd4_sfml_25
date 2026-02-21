#include "music_player.hpp"

MusicPlayer::MusicPlayer()
	: m_volume(100.f)
{
	m_filenames[MusicThemes::kMenuTheme] = "Media/Music/MenuTheme.ogg";
	m_filenames[MusicThemes::kMissionTheme] = "Media/Music/MissionTheme.ogg";
}

void MusicPlayer::Play(MusicThemes theme)
{
	std::string filename = m_filenames[theme];

	if (!m_music.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	m_music.setVolume(m_volume);
	m_music.setLooping(true);
	std::cout << "Playing " << filename << m_volume << std::endl;
	m_music.setRelativeToListener(false);
	m_music.play();
	sf::SoundSource::Status status = m_music.getStatus();
	if (status != sf::SoundSource::Status::Playing) {
		std::cout << "DEBUG: Music failed to start! Status: " << std::endl;
	}
	else {
		std::cout << "DEBUG: Music is technically playing at volume: " << m_music.getVolume() << std::endl;
	}
}

void MusicPlayer::Stop()
{
	m_music.stop();
}

void MusicPlayer::SetVolume(float volume)
{
	m_volume = volume;
}

void MusicPlayer::SetPaused(bool paused)
{
	if (paused)
		m_music.pause();
	else
		m_music.play();
}

MusicPlayer::~MusicPlayer() {
	std::cout << "CRITICAL: MusicPlayer is being DESTROYED!" << std::endl;
}
