#ifndef MESSAGETYPES_HPP
#define MESSAGETYPES_HPP

using String = std::string;

const String loginRequest = "loginRequest";
const String loginRespond = "loginRespond";
const String logoutRequest = "logoutRequest";
const String logoutRespond = "logoutRespond";
const String registrationRequest = "regRequest";
const String registrationRespond = "regRespond";
const String pendingMessagesRequest = "pendMsgRequest";
const String userListRequest = "userListRequest";
const String userListRespond = "userListRespond";
const String userChangedRespond = "userChanged";
const String plainMessage = "plainMessage";
const String convRequest = "userConvReq";
const String convRespond = "userConvResp";


const String online = "online";
const String offline = "offline";

const String success = "Success";
const String error = "Error";
const String emptyMessage = "Error. Message cannot be empty";


const char delim = '%';
const char underscore = '_';

#endif
