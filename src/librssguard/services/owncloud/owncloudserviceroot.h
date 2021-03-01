// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef OWNCLOUDSERVICEROOT_H
#define OWNCLOUDSERVICEROOT_H

#include "services/abstract/cacheforserviceroot.h"
#include "services/abstract/serviceroot.h"

#include <QMap>

class OwnCloudNetworkFactory;
class Mutex;

class OwnCloudServiceRoot : public ServiceRoot, public CacheForServiceRoot {
  Q_OBJECT

  public:
    explicit OwnCloudServiceRoot(RootItem* parent = nullptr);
    virtual ~OwnCloudServiceRoot();

    virtual bool isSyncable() const;
    virtual bool canBeEdited() const;
    virtual bool editViaGui();
    virtual bool supportsFeedAdding() const;
    virtual bool supportsCategoryAdding() const;
    virtual void start(bool freshly_activated);
    virtual QString code() const;
    virtual void saveAllCachedData(bool ignore_errors);
    virtual QVariantHash customDatabaseData() const;
    virtual void setCustomDatabaseData(const QVariantHash& data) const;

    OwnCloudNetworkFactory* network() const;

  protected:
    virtual RootItem* obtainNewTreeForSyncIn() const;

  private:
    void updateTitle();

  private:
    OwnCloudNetworkFactory* m_network;
};

#endif // OWNCLOUDSERVICEROOT_H
