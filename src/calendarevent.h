#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QString>
#include <QMetaType>

struct CalendarEvent {
    // Constructor with default values
    CalendarEvent(int id = 0,
          const QString &summary = QString(),
          const QString &location = QString(),
          const QString &description = QString(),
          int startYear = 2026,
          int startMonth = 2,
          int startDay = 12,
          int startHour = 9,
          int startMin = 0,
          int endYear = 2026,
          int endMonth = 2,
          int endDay = 12,
          int endHour = 10,
          int endMin = 0,
          int recurrenceType = 0,
          int isAllDay = 0,
          int isPriority = 0);

    // Member Variables
    int m_id;
    QString m_summary;
    QString m_location;
    QString m_description;
    int m_startYear;
    int m_startMonth;
    int m_startDay;
    int m_startHour;
    int m_startMin;
    int m_endYear;
    int m_endMonth;
    int m_endDay;
    int m_endHour;
    int m_endMin;
    int m_recurrenceType; // 0=None, 4=Yearly
    int m_isAllDay;
    int m_isPriority;

    // Equals operator for list searching
    bool operator==(const CalendarEvent &other) const;
};

inline CalendarEvent::CalendarEvent(int id, const QString &summary, const QString &location, const QString &description, int startYear, int startMonth, int startDay, int startHour, int startMin, int endYear, int endMonth, int endDay, int endHour, int endMin, int recurrenceType, int isAllDay, int isPriority)
    : m_id(id),
    m_summary(summary),
    m_location(location),
    m_description(description),
    m_startYear(startYear),
    m_startMonth(startMonth),
    m_startDay(startDay),
    m_startHour(startHour),
    m_startMin(startMin),
    m_endYear(endYear),
    m_endMonth(endMonth),
    m_endDay(endDay),
    m_endHour(endHour),
    m_endMin(endMin),
    m_recurrenceType(recurrenceType),
    m_isAllDay(isAllDay),
    m_isPriority(isPriority)
{
}

inline bool CalendarEvent::operator==(const CalendarEvent &other) const {
    return (this->m_id == other.m_id);
}

Q_DECLARE_METATYPE(CalendarEvent);

#endif // CALENDAREVENT_H
