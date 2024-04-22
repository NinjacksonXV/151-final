#include "LoopingMusic.hpp"

LoopingMusic::LoopingMusic(sf::InputSoundFile &file) : m_file(file),
                                                       m_loopBegin(0),
                                                       m_loopEnd(0),
                                                       m_loopCurrent(0)
{
    // Resize the internal buffer so that it can contain 1 second of audio samples
    m_samples.resize(m_file.getSampleRate() * m_file.getChannelCount());

    // Initialize the stream
    SoundStream::initialize(m_file.getChannelCount(), m_file.getSampleRate());
}

LoopingMusic::LoopingMusic(sf::InputSoundFile &file, MusicHandler *musicHandlerPtr) : m_file(file),
                                                                                      musicHandler(musicHandlerPtr),
                                                                                      m_loopBegin(0),
                                                                                      m_loopEnd(file.getSampleCount()),
                                                                                      m_loopCurrent(0)
{
    // Resize the internal buffer so that it can contain 1 second of audio samples
    m_samples.resize(m_file.getSampleRate() * m_file.getChannelCount());

    file.read(m_Begining, 1);
    std::cout << m_Begining[0] << '\n';
    // Initialize the stream
    SoundStream::initialize(m_file.getChannelCount(), m_file.getSampleRate());
}

LoopingMusic::~LoopingMusic()
{
    // We must stop before destroying the file
    stop();
}

sf::Time LoopingMusic::getLoopBegin() const
{
    unsigned int sampleRate = getSampleRate();
    unsigned int channelCount = getChannelCount();

    if (sampleRate && channelCount)
        return sf::seconds(static_cast<float>(m_loopBegin) / sampleRate / channelCount);

    return sf::Time::Zero;
}

sf::Time LoopingMusic::getLoopEnd() const
{
    unsigned int sampleRate = getSampleRate();
    unsigned int channelCount = getChannelCount();

    if (sampleRate && channelCount)
        return sf::seconds(static_cast<float>(m_loopEnd) / sampleRate / channelCount);

    return sf::Time::Zero;
}

void LoopingMusic::setLoopPoints(sf::Time begin, sf::Time end)
{
    std::size_t sampleCount = m_file.getSampleCount();

    // Reset to playing whole stream
    if (begin == end)
    {
        m_loopBegin = 0;
        m_loopEnd = sampleCount;
        return;
    }

    unsigned int sampleRate = getSampleRate();
    unsigned int channelCount = getChannelCount();

    begin = sf::microseconds(std::max(begin.asMicroseconds(), 0ll));
    end = sf::microseconds(std::max(end.asMicroseconds(), 0ll));

    sf::Uint64 loopBegin = static_cast<sf::Uint64>(begin.asSeconds() * sampleRate * channelCount);
    sf::Uint64 loopEnd = static_cast<sf::Uint64>(end.asSeconds() * sampleRate * channelCount);

    loopBegin = std::min(loopBegin, static_cast<sf::Uint64>(sampleCount));
    loopEnd = std::min(loopEnd, static_cast<sf::Uint64>(sampleCount));

    if (!loopEnd)
        loopEnd = sampleCount;

    loopBegin -= loopBegin % channelCount;
    loopEnd -= loopEnd % channelCount;

    m_loopBegin = loopBegin;
    m_loopEnd = loopEnd;
}

bool LoopingMusic::onGetData(Chunk &data)
{
    sf::Lock lock(m_mutex);
    // std::cout << m_loopCurrent << ", " << m_loopEnd << '\n';

    // Fill the chunk parameters
    if (data.samples[0])
    {
    }
    data.samples = &m_samples[0];
    data.sampleCount = static_cast<std::size_t>(m_file.read(&m_samples[0], m_samples.size()));

    if (!data.sampleCount)
    {
        // Check if we have reached the end of the audio file
        return data.sampleCount == m_samples.size();
    }

    // Standard non-looping case
    if (m_loopBegin == m_loopEnd || !sf::SoundStream::getLoop())
    {
        m_loopCurrent += data.sampleCount;

        // Check if we have reached the end of the audio file
        return data.sampleCount == m_samples.size();
    }

    // We are looping
    // Check for a loop transition
    if (m_loopCurrent + data.sampleCount > m_loopEnd)
    {
        std::size_t endSampleCount = std::min(static_cast<std::size_t>(m_loopEnd - m_loopCurrent), data.sampleCount);
        std::size_t beginSampleCount = m_samples.size() - endSampleCount;

        // Jump back to the beginning of the sequence
        // std::cout << "Looping? ";

        // Fill the rest of the buffer with the data at the beginning
        beginSampleCount = static_cast<std::size_t>(m_file.read(&m_samples[endSampleCount], beginSampleCount));

        data.sampleCount = endSampleCount + beginSampleCount;
        m_loopCurrent = m_loopBegin + beginSampleCount;
    }
    else
    {
        m_loopCurrent += data.sampleCount;
    }
    return data.sampleCount == m_samples.size();
}

void LoopingMusic::onSeek(sf::Time timeOffset)
{
    sf::Lock lock(m_mutex);

    sf::Uint64 sampleOffset = static_cast<sf::Uint64>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
    sampleOffset -= sampleOffset % getChannelCount();

    m_loopCurrent = sampleOffset;
    if (sampleOffset == 0 && this->musicHandler != nullptr)
    {
        std::cout << sampleOffset;
        musicHandler->loopStarted();
    }
    m_file.seek(sampleOffset);
}
