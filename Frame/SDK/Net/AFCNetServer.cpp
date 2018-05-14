///*
//* This source file is part of ArkGameFrame
//* For the latest info, see https://github.com/ArkGame
//*
//* Copyright (c) 2013-2018 ArkGame authors.
//*
//* Licensed under the Apache License, Version 2.0 (the "License");
//* you may not use this file except in compliance with the License.
//* You may obtain a copy of the License at
//*
//*     http://www.apache.org/licenses/LICENSE-2.0
//*
//* Unless required by applicable law or agreed to in writing, software
//* distributed under the License is distributed on an "AS IS" BASIS,
//* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//* See the License for the specific language governing permissions and
//* limitations under the License.
//*
//*/
//
//#include "AFCNetServer.h"
//#include <string.h>
//
//#if ARK_PLATFORM == PLATFORM_WIN
//#include <WS2tcpip.h>
//#include <winsock2.h>
//#pragma  comment(lib,"Ws2_32.lib")
//#pragma  comment(lib,"event.lib")
//#pragma  comment(lib,"event_core.lib")
//#elif ARK_PLATFORM == PLATFORM_APPLE
//#include <arpa/inet.h>
//#endif
//
//#include "event2/bufferevent_struct.h"
//#include "event2/event.h"
//#include <atomic>
//#include <memory>
//
//void AFCNetServer::Update()
//{
//    ProcessMsgLogicThread();
//}
//
//int AFCNetServer::Start(const unsigned int nMaxClient, const std::string& strAddrPort, const int nServerID, const int nThreadCount)
//{
//#ifdef _MSC_VER
//    WSADATA wsa_data;
//    WSAStartup(MAKEWORD(2, 2), &wsa_data);
//#endif
//
//    mnMaxConnect = (int)nMaxClient;
//    mstrIPPort = strAddrPort;
//#if defined(HAVE_LANG_CXX14) || defined(HAVE_LANG_CXX17)
//    m_pListenThread = std::make_unique<evpp::EventLoopThread>();
//#else
//    m_pListenThread.reset(new evpp::EventLoopThread);
//#endif
//    m_pListenThread->set_name("LisenThread");
//    m_pListenThread->Start(true);
//
//#if defined(HAVE_LANG_CXX14) || defined(HAVE_LANG_CXX17)
//    m_pTcpSrv = std::make_unique<evpp::TCPServer>(m_pListenThread->loop(), strAddrPort, "tcp_server", nThreadCount);
//#else
//    m_pTcpSrv.reset(new evpp::TCPServer(m_pListenThread->loop(), strAddrPort, "tcp_server", nThreadCount));
//#endif
//    m_pTcpSrv->SetMessageCallback(std::bind(&AFCNetServer::OnMessageInner, this, std::placeholders::_1, std::placeholders::_2));
//    m_pTcpSrv->SetConnectionCallback(std::bind(&AFCNetServer::OnClientConnectionInner, this, std::placeholders::_1));
//    m_pTcpSrv->Init();
//    m_pTcpSrv->Start();
//    bWorking = true;
//    return 0;
//}
//
//void AFCNetServer::OnMessage(const evpp::TCPConnPtr& conn, evpp::Buffer* msg, void* pData)
//{
//    AFCNetServer * pServer = (AFCNetServer*)pData;
//    if(pServer)
//    {
//        pServer->OnMessageInner(conn, msg);
//    }
//}
//
//void AFCNetServer::OnMessageInner(const evpp::TCPConnPtr& conn, evpp::Buffer* msg)
//{
//    if(conn->context().IsEmpty())
//    {
//        return;
//    }
//
//    NFCEvppNetObject* pEntity = evpp::any_cast<NFCEvppNetObject*>(conn->context());
//    if(pEntity)
//    {
//        evpp::Slice xMsgBuff;
//        if(msg)
//        {
//            xMsgBuff = msg->NextAll();
//            int nRet = pEntity->AddBuff(xMsgBuff.data(), xMsgBuff.size());
//            bool bRet = DismantleNet(pEntity);
//        }
//    }
//}
//
//void AFCNetServer::OnClientConnection(const evpp::TCPConnPtr& conn, void* pData)
//{
//    AFCNetServer * pServer = (AFCNetServer*)pData;
//    if(pServer)
//    {
//        pServer->OnClientConnectionInner(conn);
//    }
//}
//void AFCNetServer::OnClientConnectionInner(const evpp::TCPConnPtr& conn)
//{
//    if(conn->IsConnected())
//    {
//        conn->SetTCPNoDelay(true);
//        MsgEvppFromNetInfo* pMsg = new MsgEvppFromNetInfo(conn);
//        pMsg->xClientID = conn->id();
//        pMsg->nType = CONNECTED;
//        {
//            AFScopeWrLock xGuard(mRWLock);
//
//            NFCEvppNetObject* pEntity = new NFCEvppNetObject(this, pMsg->xClientID, conn);
//            bool bRet = AddNetObject(pMsg->xClientID, pEntity);
//            conn->set_context(evpp::Any(pEntity));
//
//            pEntity->mqMsgFromNet.Push(pMsg);
//        }
//    }
//    else
//    {
//        MsgEvppFromNetInfo* pMsg = new MsgEvppFromNetInfo(conn);
//        pMsg->xClientID = conn->id();
//        pMsg->nType = DISCONNECTED;
//
//
//        //娑撹崵鍤庣粙瀣╃瑝閼崇晫娲块幒銉ュ灩闂勩們鈧倷绗夐悞鎯扮箹闁插苯姘ㄩ柌搴濈啊
//        if(!conn->context().IsEmpty())
//        {
//            NFCEvppNetObject* pEntity = evpp::any_cast<NFCEvppNetObject*>(conn->context());
//            pEntity->mqMsgFromNet.Push(pMsg);
//            conn->set_context(evpp::Any(nullptr));
//        }
//    }
//}
//
//void AFCNetServer::ProcessMsgLogicThread()
//{
//    std::list<AFGUID> xNeedRemoveList;
//    {
//        AFScopeRdLock xGuard(mRWLock);
//        for(std::map<AFGUID, NFCEvppNetObject*>::iterator iter = mmObject.begin(); iter != mmObject.end(); ++iter)
//        {
//            ProcessMsgLogicThread(iter->second);
//            if(!iter->second->NeedRemove())
//            {
//                continue;
//            }
//
//            xNeedRemoveList.push_back(iter->second->GetClientID());
//        }
//    }
//
//    for(std::list<AFGUID>::iterator iter = xNeedRemoveList.begin(); iter != xNeedRemoveList.end(); ++iter)
//    {
//        AFScopeWrLock xGuard(mRWLock);
//        RemoveNetObject(*iter);
//    }
//}
//
//void AFCNetServer::ProcessMsgLogicThread(NFCEvppNetObject* pEntity)
//{
//    //Handle Msg
//    size_t nReceiveCount = pEntity->mqMsgFromNet.Count();
//    for(size_t i = 0; i < nReceiveCount; ++i)
//    {
//        MsgEvppFromNetInfo* pMsgFromNet(NULL);
//        if(!pEntity->mqMsgFromNet.Pop(pMsgFromNet))
//        {
//            break;
//        }
//
//        if(pMsgFromNet == nullptr)
//        {
//            continue;
//        }
//
//        switch(pMsgFromNet->nType)
//        {
//        case RECIVEDATA:
//            {
//                int nRet = 0;
//                if(mRecvCB)
//                {
//                    mRecvCB(pMsgFromNet->xHead, pMsgFromNet->xHead.GetMsgID(), pMsgFromNet->strMsg.c_str(), pMsgFromNet->strMsg.size(), pEntity->GetClientID());
//                }
//            }
//            break;
//        case CONNECTED:
//            {
//                mEventCB((NetEventType)pMsgFromNet->nType, pMsgFromNet->xClientID, mnServerID);
//            }
//            break;
//        case DISCONNECTED:
//            {
//                mEventCB((NetEventType)pMsgFromNet->nType, pMsgFromNet->xClientID, mnServerID);
//                pEntity->SetNeedRemove(true);
//            }
//            break;
//        default:
//            break;
//        }
//
//        delete pMsgFromNet;
//    }
//}
//
//bool AFCNetServer::Final()
//{
//    m_pTcpSrv->Stop();
//    m_pListenThread->Stop(true);
//    bWorking = false;
//    return true;
//}
//
//bool AFCNetServer::SendMsgToAllClient(const char* msg, const size_t nLen)
//{
//    std::map<AFGUID, NFCEvppNetObject*>::iterator it = mmObject.begin();
//    for(; it != mmObject.end(); ++it)
//    {
//        NFCEvppNetObject* pNetObject = (NFCEvppNetObject*)it->second;
//        if(pNetObject && !pNetObject->NeedRemove())
//        {
//            pNetObject->GetConnPtr()->Send(msg, nLen);
//        }
//    }
//
//    return true;
//}
//
//bool AFCNetServer::SendMsg(const char* msg, const size_t nLen, const AFGUID& xClient)
//{
//    AFScopeRdLock xGuard(mRWLock);
//
//    NFCEvppNetObject* pNetObject = GetNetObject(xClient);
//    if(pNetObject == nullptr)
//    {
//        return false;
//    }
//
//    pNetObject->GetConnPtr()->Send(msg, nLen);
//    return true;
//}
//
//bool AFCNetServer::AddNetObject(const AFGUID& xClientID, NFCEvppNetObject* pEntity)
//{
//    return mmObject.insert(std::make_pair(xClientID, pEntity)).second;
//}
//
//bool AFCNetServer::RemoveNetObject(const AFGUID& xClientID)
//{
//    NFCEvppNetObject* pNetObject = GetNetObject(xClientID);
//    if(pNetObject)
//    {
//        delete pNetObject;
//    }
//    return mmObject.erase(xClientID);
//}
//
//bool AFCNetServer::CloseNetObject(const AFGUID& xClientID)
//{
//    NFCEvppNetObject* pEntity = GetNetObject(xClientID);
//    if(pEntity)
//    {
//        pEntity->GetConnPtr()->Close();
//    }
//
//    return true;
//}
//
//bool AFCNetServer::DismantleNet(NFCEvppNetObject* pEntity)
//{
//    for(; pEntity->GetBuffLen() >= AFIMsgHead::ARK_MSG_HEAD_LENGTH;)
//    {
//        AFCMsgHead xHead;
//        int nMsgBodyLength = DeCode(pEntity->GetBuff(), pEntity->GetBuffLen(), xHead);
//        if(nMsgBodyLength >= 0 && xHead.GetMsgID() > 0)
//        {
//            MsgEvppFromNetInfo* pNetInfo = new  MsgEvppFromNetInfo(pEntity->GetConnPtr());
//            pNetInfo->xHead = xHead;
//            pNetInfo->nType = RECIVEDATA;
//            pNetInfo->strMsg.append(pEntity->GetBuff() + AFIMsgHead::ARK_MSG_HEAD_LENGTH, nMsgBodyLength);
//            pEntity->mqMsgFromNet.Push(pNetInfo);
//            size_t nRet = pEntity->RemoveBuff(nMsgBodyLength + AFIMsgHead::ARK_MSG_HEAD_LENGTH);
//        }
//        else
//        {
//            break;
//        }
//    }
//
//    return true;
//}
//
//bool AFCNetServer::CloseSocketAll()
//{
//    std::map<AFGUID, NFCEvppNetObject*>::iterator it = mmObject.begin();
//    for(it; it != mmObject.end(); ++it)
//    {
//        it->second->GetConnPtr()->Close();
//        delete it->second;
//    }
//
//    mmObject.clear();
//
//    return true;
//}
//
//NFCEvppNetObject* AFCNetServer::GetNetObject(const AFGUID& xClientID)
//{
//    std::map<AFGUID, NFCEvppNetObject*>::iterator it = mmObject.find(xClientID);
//    if(it != mmObject.end())
//    {
//        return it->second;
//    }
//
//    return NULL;
//}
//
//bool AFCNetServer::SendMsgWithOutHead(const uint16_t nMsgID, const char* msg, const size_t nLen, const AFGUID& xClientID, const AFGUID& xPlayerID)
//{
//    std::string strOutData;
//    AFCMsgHead xHead;
//    xHead.SetMsgID(nMsgID);
//    xHead.SetPlayerID(xPlayerID);
//    xHead.SetBodyLength(nLen);
//
//    int nAllLen = EnCode(xHead, msg, nLen, strOutData);
//    if(nAllLen == nLen + AFIMsgHead::ARK_MSG_HEAD_LENGTH)
//    {
//        return SendMsg(strOutData.c_str(), strOutData.length(), xClientID);
//    }
//
//    return false;
//}
//
//bool AFCNetServer::SendMsgToAllClientWithOutHead(const uint16_t nMsgID, const char* msg, const size_t nLen, const AFGUID& xPlayerID)
//{
//    std::string strOutData;
//    AFCMsgHead xHead;
//    xHead.SetMsgID(nMsgID);
//    xHead.SetPlayerID(xPlayerID);
//
//    int nAllLen = EnCode(xHead, msg, nLen, strOutData);
//    if(nAllLen == nLen + AFIMsgHead::ARK_MSG_HEAD_LENGTH)
//    {
//        return SendMsgToAllClient(strOutData.c_str(), strOutData.length());
//    }
//
//    return false;
//}
//
//int AFCNetServer::EnCode(const AFCMsgHead& xHead, const char* strData, const size_t len, std::string& strOutData)
//{
//    char szHead[AFIMsgHead::ARK_MSG_HEAD_LENGTH] = { 0 };
//    int nRet = xHead.EnCode(szHead);
//
//    strOutData.clear();
//    strOutData.append(szHead, AFIMsgHead::ARK_MSG_HEAD_LENGTH);
//    strOutData.append(strData, len);
//
//    return xHead.GetBodyLength() + AFIMsgHead::ARK_MSG_HEAD_LENGTH;
//}
//
//int AFCNetServer::DeCode(const char* strData, const size_t len, AFCMsgHead& xHead)
//{
//    if(len < AFIMsgHead::ARK_MSG_HEAD_LENGTH)
//    {
//        return -1;
//    }
//
//    if(AFIMsgHead::ARK_MSG_HEAD_LENGTH != xHead.DeCode(strData))
//    {
//        return -2;
//    }
//
//    if(xHead.GetBodyLength() > (len - AFIMsgHead::ARK_MSG_HEAD_LENGTH))
//    {
//        return -3;
//    }
//
//    return xHead.GetBodyLength();
//}
//
