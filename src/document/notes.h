/****************************************************************************
**
** Copyright (C) TERIFLIX Entertainment Spaces Pvt. Ltd. Bengaluru
** Author: Prashanth N Udupa (prashanth.udupa@teriflix.com)
**
** This code is distributed under GPL v3. Complete text of the license
** can be found here: https://www.gnu.org/licenses/gpl-3.0.txt
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef NOTES_H
#define NOTES_H

#include <QJsonValue>
#include <QQmlListProperty>
#include <QAbstractListModel>

#include "attachments.h"
#include "qobjectproperty.h"

class Form;
class Prop;
class Notes;
class Scene;
class Location;
class Character;
class Structure;
class Attachments;
class Relationship;
class ScreenplayElement;

class Note : public QObject, public QObjectSerializer::Interface
{
    Q_OBJECT
    Q_INTERFACES(QObjectSerializer::Interface)

public:
    Note(QObject *parent=nullptr);
    ~Note();
    Q_SIGNAL void aboutToDelete(Note *ptr);

    Q_PROPERTY(Notes* notes READ notes CONSTANT STORED false)
    Notes *notes() const;

    enum Type
    {
        TextNoteType,
        FormNoteType
    };
    Q_ENUM(Type)
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
    Type type() const { return m_type; }
    Q_SIGNAL void typeChanged();

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    void setTitle(const QString &val);
    QString title() const { return m_title; }
    Q_SIGNAL void titleChanged();

    Q_PROPERTY(QString summary READ summary WRITE setSummary NOTIFY summaryChanged STORED false)
    void setSummary(const QString &val);
    QString summary() const { return m_summary; }
    Q_SIGNAL void summaryChanged();

    Q_PROPERTY(QJsonValue content READ content WRITE setContent NOTIFY contentChanged)
    void setContent(const QJsonValue &val);
    QJsonValue content() const { return m_content; }
    Q_SIGNAL void contentChanged();

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    void setColor(const QColor &val);
    QColor color() const { return m_color; }
    Q_SIGNAL void colorChanged();

    Q_PROPERTY(QString formId READ formId NOTIFY formIdChanged)
    QString formId() const { return m_formId; }
    Q_SIGNAL void formIdChanged();

    Q_PROPERTY(Form* form READ form RESET resetForm NOTIFY formChanged STORED false)
    Form* form() const { return m_form; }
    Q_SIGNAL void formChanged();

    Q_PROPERTY(QJsonObject formData READ formData WRITE setFormData NOTIFY formDataChanged)
    void setFormData(const QJsonObject &val);
    QJsonObject formData() const { return m_formData; }
    Q_SIGNAL void formDataChanged();

    Q_INVOKABLE void setFormData(const QString &key, const QJsonValue &value);
    Q_INVOKABLE QJsonValue getFormData(const QString &key) const;

    Q_PROPERTY(Attachments* attachments READ attachments CONSTANT)
    Attachments *attachments() const { return m_attachments; }

    Q_SIGNAL void noteModified();

    // QObjectSerializer::Interface interface
    void prepareForSerialization();
    void serializeToJson(QJsonObject &json) const;
    void deserializeFromJson(const QJsonObject &);

private:
    void setType(Type val);
    void setFormId(const QString &val);
    void setForm(Form* val);
    void resetForm();
    void addAttachment(Attachment *ptr);

private:
    friend class Notes;
    QString m_title;
    QString m_formId;
    QString m_summary;
    QJsonValue m_content;
    QJsonObject m_formData;
    QColor m_color = Qt::white;
    Type m_type = TextNoteType;
    QObjectProperty<Form> m_form;
    Attachments *m_attachments = new Attachments(this);
};

class RemoveNoteUndoCommand;
class Notes : public ObjectListPropertyModel<Note *>, public QObjectSerializer::Interface
{
    Q_OBJECT
    Q_INTERFACES(QObjectSerializer::Interface)

public:
    Notes(QObject *parent = nullptr);
    ~Notes();
    Q_SIGNAL void aboutToDelete(Notes *ptr);

    enum OwnerType
    {
        StructureOwner,
        SceneOwner,
        BreakOwner, // Act, Episode etc..
        CharacterOwner,
        RelationshipOwner,
        LocationOwner,
        PropOwner,
        OtherOwner
    };
    Q_ENUM(OwnerType)
    Q_PROPERTY(OwnerType ownerType READ ownerType CONSTANT)
    OwnerType ownerType() const;

    Q_PROPERTY(QObject* owner READ owner STORED false CONSTANT)
    QObject *owner() const { return this->QObject::parent(); }

    Q_PROPERTY(Structure* structure READ structure STORED false CONSTANT)
    Structure *structure() const;

    Q_PROPERTY(ScreenplayElement *breakElement READ breakElement STORED false CONSTANT)
    ScreenplayElement *breakElement() const;

    Q_PROPERTY(Scene* scene READ scene STORED false CONSTANT)
    Scene *scene() const;

    Q_PROPERTY(Character* character READ character STORED false CONSTANT)
    Character *character() const;

    Q_PROPERTY(Relationship* relationship READ relationship STORED false CONSTANT)
    Relationship *relationship() const;

    /*
    Q_PROPERTY(Location* location READ location STORED false CONSTANT)
    Location *location() const { return nullptr; }

    Q_PROPERTY(Prop* prop READ prop STORED false CONSTANT)
    Prop *prop() const { return nullptr; }
    */

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    void setColor(const QColor &val);
    QColor color() const { return m_color; }
    Q_SIGNAL void colorChanged();

    Q_INVOKABLE Note *addTextNote();
    Q_INVOKABLE Note *addFormNote(const QString &id);
    Q_INVOKABLE void removeNote(Note *ptr);
    Q_INVOKABLE Note *noteAt(int index) const;
    Q_INVOKABLE Note *firstNote() const { return this->noteAt(0); }
    Q_INVOKABLE Note *lastNote() const { return this->noteAt(this->noteCount()-1); }
    Q_INVOKABLE void clearNotes();

    Q_PROPERTY(int noteCount READ noteCount NOTIFY noteCountChanged)
    int noteCount() const { return this->objectCount(); }
    Q_SIGNAL void noteCountChanged();

    Q_PROPERTY(int compatibleFormType READ compatibleFormType CONSTANT)
    int compatibleFormType() const { return m_compatibleFormType; }

    Q_SIGNAL void notesModified();

    // QObjectSerializer::Interface interface
    void serializeToJson(QJsonObject &json) const;
    void deserializeFromJson(const QJsonObject &);

    // Helper method to port notes from old notes[]
    void loadOldNotes(const QJsonArray &array);

private:
    void addNote(Note *ptr);
    void setNotes(const QList<Note*> &list);

private:
    friend class RemoveNoteUndoCommand;
    int m_compatibleFormType = -1;
    QColor m_color = Qt::white;
    OwnerType m_ownerType = OtherOwner;
};

#endif // NOTES_H