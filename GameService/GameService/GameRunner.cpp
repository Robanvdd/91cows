// Copyright (c) 2019 by Phenom-World B.V.
// All rights reserved. This file includes confidential and proprietary information of Phenom-World B.V.

#include "GameRunner.h"

#include <QTimerEvent>

GameRunner::GameRunner(QObject *parent)
    : QObject(parent)
{
    m_game.stop();
}

void GameRunner::createNewGame(const GameOptions& gameOptions)
{
    m_game = Game(gameOptions);
    m_timerId = startTimer(100);
}

void GameRunner::startGame()
{
    m_game.start();
}

void GameRunner::stopGame()
{
    m_game.stop();
}

void GameRunner::setBotLocations(const QVector<BotInfo>& botLocations)
{
    m_game.setBotLocations(botLocations);
}

void GameRunner::timerEvent(QTimerEvent* event)
{
    if (m_timerId == event->timerId())
    {
        m_game.handleTick();
        emit sendOutObscuredState(m_game.getObscuredState());
        emit sendOutRevealedState(m_game.getRevealedState());
    }
}
