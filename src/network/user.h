/****************************************************************************
**
** Copyright (C) VCreate Logic Pvt. Ltd. Bengaluru
** Author: Prashanth N Udupa (prashanth@scrite.io)
**
** This code is distributed under GPL v3. Complete text of the license
** can be found here: https://www.gnu.org/licenses/gpl-3.0.txt
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef USER_H
#define USER_H

#include <QUrl>
#include <QDateTime>
#include <QQmlEngine>
#include <QJsonValue>
#include <QQuickImageProvider>

struct UserInstallationInfo
{
    Q_GADGET
    QML_ELEMENT
    QML_UNCREATABLE("Instantiation from QML not allowed.")

public:
    UserInstallationInfo() { }
    UserInstallationInfo(const QJsonObject &object);
    UserInstallationInfo(const UserInstallationInfo &other);

    bool operator==(const UserInstallationInfo &other) const;
    bool operator!=(const UserInstallationInfo &other) const { return !(*this == other); }
    UserInstallationInfo &operator=(const UserInstallationInfo &other);

    Q_PROPERTY(bool valid READ isValid)
    bool isValid() const { return !id.isEmpty(); }

    Q_PROPERTY(QString id MEMBER id)
    QString id;

    Q_PROPERTY(QString clientId MEMBER clientId)
    QString clientId;

    Q_PROPERTY(QString deviceId MEMBER deviceId)
    QString deviceId;

    Q_PROPERTY(QString platform MEMBER platform)
    QString platform;

    Q_PROPERTY(QString platformVersion MEMBER platformVersion)
    QString platformVersion;

    Q_PROPERTY(QString platformType MEMBER platformType)
    QString platformType;

    Q_PROPERTY(QString appVersion MEMBER appVersion)
    QString appVersion;

    Q_PROPERTY(QStringList pastAppVersions MEMBER pastAppVersions)
    QStringList pastAppVersions;

    Q_PROPERTY(QDateTime creationDate MEMBER creationDate)
    QDateTime creationDate;

    Q_PROPERTY(QDateTime lastActivationDate MEMBER lastActivationDate)
    QDateTime lastActivationDate;

    Q_PROPERTY(QDateTime lastSessionDate MEMBER lastSessionDate)
    QDateTime lastSessionDate;

    Q_PROPERTY(bool activated MEMBER activated)
    bool activated = false;

    Q_PROPERTY(bool isCurrent READ isCurrent)
    bool isCurrent() const; // TODO
};
Q_DECLARE_METATYPE(UserInstallationInfo)
Q_DECLARE_METATYPE(QList<UserInstallationInfo>)

struct UserSubscriptionPlanInfo
{
    Q_GADGET
    QML_ELEMENT
    QML_UNCREATABLE("Instantiation from QML not allowed.")

public:
    UserSubscriptionPlanInfo() { }
    UserSubscriptionPlanInfo(const QJsonObject &object);
    UserSubscriptionPlanInfo(const UserSubscriptionPlanInfo &other);

    bool operator==(const UserSubscriptionPlanInfo &other) const;
    bool operator!=(const UserSubscriptionPlanInfo &other) const { return !(*this == other); }
    UserSubscriptionPlanInfo &operator=(const UserSubscriptionPlanInfo &other);

    Q_PROPERTY(QString name MEMBER name)
    QString name;

    Q_PROPERTY(QString kind MEMBER kind)
    QString kind;

    Q_PROPERTY(QString title MEMBER title)
    QString title;

    Q_PROPERTY(QString subtitle MEMBER subtitle)
    QString subtitle;

    Q_PROPERTY(int duration MEMBER duration)
    int duration = 0;

    Q_PROPERTY(bool exclusive MEMBER exclusive)
    bool exclusive = false;

    Q_PROPERTY(QString currency MEMBER currency)
    QString currency;

    Q_PROPERTY(qreal price MEMBER price)
    qreal price = 0;

    Q_PROPERTY(QStringList features MEMBER features)
    QStringList features;

    Q_PROPERTY(QString featureNote MEMBER featureNote)
    QString featureNote;

    Q_PROPERTY(int devices MEMBER devices)
    int devices = 1;
};
Q_DECLARE_METATYPE(UserSubscriptionPlanInfo)
Q_DECLARE_METATYPE(QList<UserSubscriptionPlanInfo>)

struct UserSubscriptionInfo
{
    Q_GADGET
    QML_ELEMENT
    QML_UNCREATABLE("Instantiation from QML not allowed.")

public:
    UserSubscriptionInfo() { }
    UserSubscriptionInfo(const QJsonObject &object);
    UserSubscriptionInfo(const UserSubscriptionInfo &other);

    bool operator==(const UserSubscriptionInfo &other) const;
    bool operator!=(const UserSubscriptionInfo &other) const { return !(*this == other); }
    UserSubscriptionInfo &operator=(const UserSubscriptionInfo &other);

    Q_PROPERTY(bool valid READ isValid)
    bool isValid() const { return !id.isEmpty(); }

    Q_PROPERTY(QString id MEMBER id)
    QString id;

    Q_PROPERTY(QString kind MEMBER kind)
    QString kind;

    Q_PROPERTY(UserSubscriptionPlanInfo plan MEMBER plan)
    UserSubscriptionPlanInfo plan;

    Q_PROPERTY(QDateTime from MEMBER from)
    QDateTime from;

    Q_PROPERTY(QDateTime until MEMBER until)
    QDateTime until;

    Q_PROPERTY(QString wc_order_id MEMBER orderId)
    Q_PROPERTY(QString orderId MEMBER orderId)
    QString orderId;

    Q_PROPERTY(QUrl detailsUrl MEMBER detailsUrl)
    QUrl detailsUrl;

    Q_PROPERTY(bool isActive MEMBER isActive)
    bool isActive = false;

    Q_PROPERTY(bool isUpcoming MEMBER isUpcoming)
    bool isUpcoming = false;

    Q_PROPERTY(bool hasExpired MEMBER hasExpired)
    bool hasExpired = false;

    Q_PROPERTY(int daysToUntil READ daysToUntil)
    int daysToUntil() const { return QDateTime::currentDateTime().daysTo(this->until) + 1; }

    Q_PROPERTY(int daysToFrom READ daysToFrom)
    int daysToFrom() const { return QDateTime::currentDateTime().daysTo(this->from) + 1; }

    Q_PROPERTY(QString description READ description)
    QString description() const;

    // feature is anything from Scrite::AppFeature
    Q_INVOKABLE bool isFeatureEnabled(int feature) const;
    Q_INVOKABLE bool isFeatureNameEnabled(const QString &featureName) const;
};
Q_DECLARE_METATYPE(UserSubscriptionInfo)
Q_DECLARE_METATYPE(QList<UserSubscriptionInfo>)

struct UserInfo
{
    Q_GADGET
    QML_ELEMENT
    QML_UNCREATABLE("Instantiation from QML not allowed.")

public:
    UserInfo() { }
    UserInfo(const QJsonObject &object);
    UserInfo(const UserInfo &other);

    bool operator==(const UserInfo &other) const;
    bool operator!=(const UserInfo &other) const { return !(*this == other); }
    UserInfo &operator=(const UserInfo &other);

    Q_PROPERTY(bool valid READ isValid)
    bool isValid() const { return !id.isEmpty(); }

    Q_PROPERTY(QString id MEMBER id)
    QString id;

    Q_PROPERTY(QString email MEMBER email)
    QString email;

    Q_PROPERTY(QDateTime signUpDate MEMBER signUpDate)
    QDateTime signUpDate;

    Q_PROPERTY(QDateTime timestamp MEMBER timestamp)
    QDateTime timestamp;

    Q_PROPERTY(QString firstName MEMBER firstName)
    QString firstName;

    Q_PROPERTY(QString lastName MEMBER lastName)
    QString lastName;

    Q_PROPERTY(QString fullName MEMBER fullName)
    QString fullName;

    Q_PROPERTY(QString experience MEMBER experience)
    QString experience;

    Q_PROPERTY(QString city MEMBER city)
    QString city;

    Q_PROPERTY(QString country MEMBER country)
    QString country;

    Q_PROPERTY(QString wdyhas MEMBER wdyhas)
    QString wdyhas;

    Q_PROPERTY(bool consentToActivityLog MEMBER consentToActivityLog)
    bool consentToActivityLog = false;

    Q_PROPERTY(bool consentToEmail MEMBER consentToEmail)
    bool consentToEmail = false;

    Q_PROPERTY(QList<UserInstallationInfo> installations MEMBER installations)
    QList<UserInstallationInfo> installations;

    Q_PROPERTY(QList<UserSubscriptionInfo> subscriptions MEMBER subscriptions)
    QList<UserSubscriptionInfo> subscriptions;

    Q_PROPERTY(UserSubscriptionInfo publicBetaSubscription MEMBER publicBetaSubscription)
    UserSubscriptionInfo publicBetaSubscription;

    Q_PROPERTY(int activeInstallationCount MEMBER activeInstallationCount)
    int activeInstallationCount = 0;

    Q_PROPERTY(bool hasActiveSubscription MEMBER hasActiveSubscription)
    bool hasActiveSubscription = false;

    Q_PROPERTY(bool hasUpcomingSubscription MEMBER hasUpcomingSubscription)
    bool hasUpcomingSubscription = false;

    Q_PROPERTY(bool hasTrialSubscription MEMBER hasTrialSubscription)
    bool hasTrialSubscription = false;

    Q_PROPERTY(int paidSubscriptionCount MEMBER paidSubscriptionCount)
    int paidSubscriptionCount = 0;

    Q_PROPERTY(QDateTime subscribedUntil MEMBER subscribedUntil)
    QDateTime subscribedUntil;

    Q_PROPERTY(bool isEarlyAdopter MEMBER isEarlyAdopter)
    bool isEarlyAdopter = false;

    Q_PROPERTY(QStringList availableFeatures MEMBER availableFeatures)
    QStringList availableFeatures;

    Q_PROPERTY(QUrl badgeImageUrl MEMBER badgeImageUrl)
    QUrl badgeImageUrl;

    Q_PROPERTY(QColor badgeTextColor MEMBER badgeTextColor)
    QColor badgeTextColor = Qt::white;

    Q_INVOKABLE bool isFeatureEnabled(int feature) const;
    Q_INVOKABLE bool isFeatureNameEnabled(const QString &featureName) const;
};
Q_DECLARE_METATYPE(UserInfo)

struct UserMessageButton
{
    Q_GADGET
    QML_ELEMENT

public:
    UserMessageButton() { }
    UserMessageButton(const QJsonObject &object);
    UserMessageButton(const UserMessageButton &other);

    bool operator==(const UserMessageButton &other) const;
    bool operator!=(const UserMessageButton &other) const { return !(*this == other); }
    UserMessageButton &operator=(const UserMessageButton &other);

    enum Type { LinkType, OtherType };
    Q_ENUM(Type)

    Q_PROPERTY(Type type MEMBER type)
    Type type = LinkType;

    Q_PROPERTY(QString text MEMBER text)
    QString text;

    enum Action { UrlAction, CommandAction, OtherAction };
    Q_ENUM(Action)

    Q_PROPERTY(Action action MEMBER action)
    Action action = UrlAction;

    Q_PROPERTY(QString endpoint MEMBER endpoint)
    QString endpoint;

    Q_PROPERTY(QJsonValue params MEMBER params)
    QJsonValue params;
};
Q_DECLARE_METATYPE(UserMessageButton)
Q_DECLARE_METATYPE(QList<UserMessageButton>)

struct UserMessage
{
    Q_GADGET
    QML_ELEMENT

public:
    UserMessage() { }
    UserMessage(const QJsonObject &object);
    UserMessage(const UserMessage &other);

    bool operator==(const UserMessage &other) const;
    bool operator!=(const UserMessage &other) const { return !(*this == other); }
    UserMessage &operator=(const UserMessage &other);

    Q_PROPERTY(bool valid READ isValid)
    bool isValid() const { return !id.isEmpty(); }

    Q_PROPERTY(QString id MEMBER id)
    QString id;

    enum Type { DefaultType, ImportantType };
    Q_ENUM(Type)

    Q_PROPERTY(Type type MEMBER type)
    Type type = DefaultType;

    Q_PROPERTY(QString from MEMBER from)
    QString from;

    Q_PROPERTY(QDateTime timestamp MEMBER timestamp)
    QDateTime timestamp;

    Q_PROPERTY(QDateTime expiresOn MEMBER expiresOn)
    QDateTime expiresOn;

    Q_PROPERTY(bool hasExpired READ hasExpired)
    bool hasExpired() const
    {
        return this->isValid() && QDateTime::currentDateTime() > this->expiresOn;
    }

    Q_PROPERTY(QString subject MEMBER subject)
    QString subject;

    Q_PROPERTY(QUrl image MEMBER image)
    QUrl image;

    Q_PROPERTY(QString body MEMBER body)
    QString body;

    Q_PROPERTY(bool read MEMBER read)
    bool read = false;

    Q_PROPERTY(QList<UserMessageButton> buttons MEMBER buttons)
    QList<UserMessageButton> buttons;
};
Q_DECLARE_METATYPE(UserMessage)
Q_DECLARE_METATYPE(QList<UserMessage>)

class User : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Instantiation from QML not allowed.")

public:
    static User *instance();
    ~User();

    Q_PROPERTY(bool loggedIn READ isLoggedIn NOTIFY infoChanged)
    bool isLoggedIn() const;
    Q_SIGNAL void loggedInChanged();

    Q_PROPERTY(UserInfo info READ info NOTIFY infoChanged)
    UserInfo info() const { return m_info; }
    Q_SIGNAL void infoChanged();

    Q_SLOT void logActivity1(const QString &activity)
    {
        this->logActivity2(activity, QJsonValue());
    }
    Q_SLOT void logActivity2(const QString &activity, const QJsonValue &data);

    Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)
    bool isBusy() const;
    Q_SIGNAL void busyChanged();

    Q_PROPERTY(QList<UserMessage> messages READ messages WRITE setMessages NOTIFY messagesChanged)
    QList<UserMessage> messages() const { return m_messages; }
    Q_SIGNAL void messagesChanged();

    Q_PROPERTY(int totalMessageCount READ totalMessageCount NOTIFY messagesChanged)
    int totalMessageCount() const { return m_messages.size(); }

    Q_PROPERTY(int unreadMessageCount READ unreadMessageCount NOTIFY messagesChanged)
    int unreadMessageCount() const;

    Q_INVOKABLE void checkForMessages();
    Q_INVOKABLE void markMessagesAsRead();

signals:
    void subscriptionAboutToExpire(int days);
    void notifyImportantMessages(const QList<UserMessage> &messages);

private:
    User(QObject *parent = nullptr);

    void setInfo(const UserInfo &val);
    void setMessages(const QList<UserMessage> &val);
    void checkIfSubscriptionIsAboutToExpire();

    void storeMessages();
    void loadStoredMessages();

public: // Don't use these methods
    void loadInfoFromStorage();
    void loadInfoUsingRestApiCall();

protected:
    void childEvent(QChildEvent *e);

private:
    UserInfo m_info;
    QList<UserMessage> m_messages;
};

class AppFeature : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AppFeature(QObject *parent = nullptr);
    ~AppFeature();

    static bool isEnabled(int feature);
    static bool isEnabled(const QString &featureName);

    Q_PROPERTY(QString featureName READ featureName WRITE setFeatureName NOTIFY featureNameChanged)
    void setFeatureName(const QString &val);
    QString featureName() const { return m_featureName; }
    Q_SIGNAL void featureNameChanged();

    Q_PROPERTY(int feature READ feature WRITE setFeature NOTIFY featureChanged)
    void setFeature(int val);
    int feature() const { return m_feature; }
    Q_SIGNAL void featureChanged();

    Q_PROPERTY(bool enabled READ isEnabled NOTIFY enabledChanged)
    bool isEnabled() const { return m_enabled; }
    Q_SIGNAL void enabledChanged();

private:
    void reevaluate();
    void setEnabled(bool val);

private:
    QString m_featureName;
    int m_feature = -1;
    bool m_enabled = false;
};

#endif // USER_H
