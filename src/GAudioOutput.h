/*=====================================================================

PIXHAWK Micro Air Vehicle Flying Robotics Toolkit

(c) 2009, 2010 PIXHAWK PROJECT  <http://pixhawk.ethz.ch>

This file is part of the PIXHAWK project

    PIXHAWK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PIXHAWK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PIXHAWK. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of audio output
 *
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef GAUDIOOUTPUT_H
#define GAUDIOOUTPUT_H

#include <QObject>
#include <QTimer>
#include <QStringList>
#include <QQueue>
#ifndef NO_TEXT_TO_SPEECH
#include <QtSpeech>
#endif

/**
 * @brief Audio Output (speech synthesizer and "beep" output)
 * This class follows the singleton design pattern
 * @see http://en.wikipedia.org/wiki/Singleton_pattern
 */
class GAudioOutput : public QObject
{
    Q_OBJECT
public:
    /** @brief Get the singleton instance */
    static GAudioOutput* instance();
    /** @brief List available voices */
    QStringList listVoices(void);
    enum {
        VOICE_MALE = 0,
        VOICE_FEMALE
    } QGVoice;

    /** @brief Get the mute state */
    bool isMuted();

public slots:
    /** @brief Say this text if current output priority matches */
    bool say(QString text, int severity=1);
    /** @brief Play alert sound and say notification message */
    bool alert(QString text);
    /** @brief Start emergency sound */
    bool startEmergency();
    /** @brief Stop emergency sound */
    bool stopEmergency();
    /** @brief Select female voice */
    void selectFemaleVoice();
    /** @brief Select male voice */
    void selectMaleVoice();
    /** @brief Play emergency sound once */
    void beep();
    /** @brief Notify about positive event */
    void notifyPositive();
    /** @brief Notify about negative event */
    void notifyNegative();
    /** @brief Mute/unmute sound */
    void mute(bool mute);

signals:
    void mutedChanged(bool);

protected:
#ifndef NO_TEXT_TO_SPEECH
    QtSpeech* speech;
#endif
    int voiceIndex;   ///< The index of the voice to use
    bool emergency;   ///< Emergency status flag
    QTimer* emergencyTimer;
    bool muted;
    QQueue<QString> voiceQueue;
    bool isSpeaking;

private slots:
    void advanceSpeechQueue();
    void sayText(QString text);

private:
    GAudioOutput(QObject* parent=NULL);
//    ~GAudioOutput();
};

#endif // AUDIOOUTPUT_H
