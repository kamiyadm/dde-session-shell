/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PUBLIC_FUNC_H
#define PUBLIC_FUNC_H

#include <QPixmap>
#include <QApplication>
#include <QIcon>
#include <QImageReader>
#include <QSettings>
#include <QString>

QPixmap loadPixmap(const QString &file);

/**
 * @brief 获取图像共享内存
 * 
 * @param uid 当前用户ID
 * @param purpose 图像用途，1是锁屏、关机、登录，2是启动器，3-19是工作区
 * @return QString Qt的共享内存key
 */
QString readSharedImage(uid_t uid, int purpose);

template <typename T>
T findValueByQSettings(const QStringList &configFiles,
                       const QString &group,
                       const QString &key,
                       const QVariant &failback)
{
    for (const QString &path : configFiles) {
        QSettings settings(path, QSettings::IniFormat);
        if (!group.isEmpty()) {
            settings.beginGroup(group);
        }

        const QVariant& v = settings.value(key);
        if (v.isValid()) {
            T t = v.value<T>();
            return t;
        }
    }

    return failback.value<T>();
}

/**
 * @brief 是否使用深度认证，不使用域管认证。
 * 
 * @return true 使用深度认证
 * @return false 使用域管认证
 */
bool isDeepinAuth();

/**
 * @brief 捕获程序异常退出
 *
 * @param sig 异常退出信号
 */
void sig_crash(int sig);

/**
 * @brief 初始化需要捕获的异常信号
 */

void init_sig_crash();

#endif // PUBLIC_FUNC_H
