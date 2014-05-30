/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtCore/QDebug>

#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "qml/QmlVideoPlayer.h"

VlcQmlVideoPlayer::VlcQmlVideoPlayer(QQuickItem *parent)
    : VlcQmlVideoObject(parent),
      _hasMedia(false)
{
    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _audioManager = new VlcAudio(_player);
}

VlcQmlVideoPlayer::~VlcQmlVideoPlayer()
{
    _player->stop();

    delete _audioManager;
    delete _media;
    delete _player;
    delete _instance;
}

void VlcQmlVideoPlayer::close()
{
    _hasMedia = false;

    _player->stop();
}

void VlcQmlVideoPlayer::openFile(const QString &file)
{
    if (_media)
        delete _media;

    _media = new VlcMedia(file, true, _instance);

    openInternal();
}

void VlcQmlVideoPlayer::openStream(const QString &stream)
{
    if (_media)
        delete _media;

    _media = new VlcMedia(stream, false, _instance);

    openInternal();
}

void VlcQmlVideoPlayer::openInternal()
{
    _player->open(_media);
    connectToMediaPlayer(_player);

    _hasMedia = true;
}

void VlcQmlVideoPlayer::pause()
{
    _player->pause();
}

void VlcQmlVideoPlayer::play()
{
    _player->play();
}

void VlcQmlVideoPlayer::stop()
{
    _player->stop();
    disconnectFromMediaPlayer(_player);
}
