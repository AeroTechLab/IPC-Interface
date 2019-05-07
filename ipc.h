////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Copyright (c) 2016-2017 Leonardo Consoni <consoni_2519@hotmail.com>       //
//                                                                            //
//  This file is part of RobRehabSystem.                                      //
//                                                                            //
//  RobRehabSystem is free software: you can redistribute it and/or modify    //
//  it under the terms of the GNU Lesser General Public License as published  //
//  by the Free Software Foundation, either version 3 of the License, or      //
//  (at your option) any later version.                                       //
//                                                                            //
//  RobRehabSystem is distributed in the hope that it will be useful,         //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of            //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              //
//  GNU Lesser General Public License for more details.                       //
//                                                                            //
//  You should have received a copy of the GNU Lesser General Public License  //
//  along with RobRehabSystem. If not, see <http://www.gnu.org/licenses/>.    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


/// @file ipc.h
/// @brief Asynchronous IP network connection abstraction.
///
/// Library that combines threading utilities with the socket connection library 
/// to provide asyncronous and thread-safe network communication methods.           

#ifndef IPC_H
#define IPC_H


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define IPC_MAX_MESSAGE_LENGTH 512        ///< Maximum allowed length of messages transmitted through an IP connection

#define IPC_INVALID_CONNECTION NULL       ///< Connection identifier to be returned on initialization errors

#ifdef _WIN32
typedef char Byte;
#else
typedef uint8_t Byte;
#endif

typedef Byte Message[ IPC_MAX_MESSAGE_LENGTH ];

typedef void* IPCConnection;              ///< Opaque type to reference encapsulated IP connection structure

/// Defined possible communication modes/protocols enumeration
enum IPCMode
{ 
  IPC_SERVER,                             ///< Receive from many clients, send to many clients
  IPC_CLIENT,                             ///< Send to one server, receive from one server
  IPC_PUB,                                ///< Send to many subscribers
  IPC_SUB,                                ///< Receive from one publisher
  IPC_REQ,                                ///< Send request to one replier, wait for reply
  IPC_REP                                 ///< Send reply to one requester after receiving request
};


/// @brief Creates a new IPC connection (with defined properties) for the underlying implementation                              
/// @param[in] mode configuration variable defining the connection operation mode                           
/// @param[in] host string identifying your process "location" for the underlying implementation    
/// @param[in] channel string identifying your process data channel for the underlying implementation 
/// @return unique generic identifier for newly created connection (IPC_INVALID_CONNECTION on error) 
IPCConnection IPC_OpenConnection( enum IPCMode mode, const char* host, const char* channel );

/// @brief Handle termination of connection corresponding to given identifier                             
/// @param[in] connection connection identifier
void IPC_CloseConnection( IPCConnection connection );

/// @brief Pops first (oldest) queued message from read queue of client connection corresponding to given identifier                      
/// @param[in] connection client connection identifier  
/// @param[in] message message byte array pointer 
/// @return pointer to message string, overwritten on next call to ReadMessage() (NULL on error or no message available)  
bool IPC_ReadMessage( IPCConnection connection, Byte* message );
                                                                           
/// @brief Pushes given message string to write queue of connection corresponding to given identifier                                                
/// @param[in] connection connection identifier   
/// @param[in] message message byte array pointer  
/// @return true on success, false on error  
bool IPC_WriteMessage( IPCConnection connection, const Byte* message );


#endif // IPC_H 
