/*MT*

    MediaTomb - http://www.mediatomb.cc/

    upnp_cm.h - this file is part of MediaTomb.

    Copyright (C) 2005 Gena Batyan <bgeradz@mediatomb.cc>,
                       Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>

    Copyright (C) 2006-2010 Gena Batyan <bgeradz@mediatomb.cc>,
                            Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>,
                            Leonhard Wimmer <leo@mediatomb.cc>

    Copyright (C) 2016-2023 Gerbera Contributors

    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.

    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    version 2 along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.

    $Id$
*/

/// \file upnp_cm.h
/// \brief Definition of the ConnectionManagerService class.
#ifndef __UPNP_CM_H__
#define __UPNP_CM_H__

#include <memory>

#include <upnp.h>

#include "common.h"
#include "context.h"

class ActionRequest;
class CdsObject;
class SubscriptionRequest;
class UpnpXMLBuilder;

/// \brief This class is responsible for the UPnP Connection Manager Service operations.
///
/// Handles subscription and action invocation requests for the Connection Manager.
class ConnectionManagerService {
protected:
    /// \brief UPnP standard defined action: GetCurrentConnectionIDs()
    /// \param request Incoming ActionRequest.
    ///
    /// GetCurrentConnectionIDs(string ConnectionIDs)
    ///
    /// This is currently unsupported (returns empty string)
    void doGetCurrentConnectionIDs(ActionRequest& request) const;

    /// \brief UPnP standard defined action: GetCurrentConnectionInfo()
    /// \param request Incoming ActionRequest.
    ///
    /// GetCurrentConnectionInfo(i4 ConnectoinID, i4 RcsID, i4 AVTransportID, string ProtocolInfo,
    /// string PeerConnectionManager, i4 PeerConnectionID, string Direction, string Status)
    ///
    /// This action is currently unsupported.
    void doGetCurrentConnectionInfo(ActionRequest& request) const;

    /// \brief UPnP standard defined action: GetProtocolInfo()
    /// \param request Incoming ActionRequest.
    ///
    /// GetProtocolInfo(string Source, string Sink)
    void doGetProtocolInfo(ActionRequest& request) const;

    std::shared_ptr<Config> config;
    std::shared_ptr<Database> database;

    std::shared_ptr<UpnpXMLBuilder> xmlBuilder;
    UpnpDevice_Handle deviceHandle;

public:
    /// \brief Constructor for the CMS, saves the service type and service id
    /// in internal variables.
    /// \todo Check if it makes sense to use it as it is done now...why not define them as constants?
    explicit ConnectionManagerService(const std::shared_ptr<Context>& context,
        std::shared_ptr<UpnpXMLBuilder> xmlBuilder, UpnpDevice_Handle deviceHandle);

    /// \brief Dispatches the ActionRequest between the available actions.
    /// \param request Incoming ActionRequest.
    ///
    /// This function looks at the incoming ActionRequest and passes it on
    /// to the appropriate action for processing.
    void processActionRequest(ActionRequest& request) const;

    /// \brief Processes an incoming SubscriptionRequest.
    /// \param request Incoming SubscriptionRequest.
    ///
    /// Looks at the incoming SubscriptionRequest and accepts the subscription
    /// if everything is ok.
    void processSubscriptionRequest(const SubscriptionRequest& request) const;

    /// \brief Sends out an event to all subscribed devices.
    /// \param sourceProtocol_CSV Comma Separated Value list of protocol information
    ///
    /// Sends out an update with protocol information to all subscribed devices
    void sendSubscriptionUpdate(const std::string& sourceProtocolCsv);
};

#endif // __UPNP_CM_H__
