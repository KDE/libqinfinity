#ifndef QINFINITY_Q_TEXT_PLUGIN_H
#define QINFINITY_Q_TEXT_PLUGIN_H

namespace QInfinity
{

InfSession *qinf_textplugin_session_new( InfIo *io,
    InfCommunicationManager *manager,
    InfCommunicationJoinedGroup *sync_group,
    InfXmlConnection *sync_connection,
    void *user_data );

class TextPlugin
{

    public:
        TextPlugin();

    private:
        static session_new_cb( InfIo *io,


        InfcNotePlugin notePlugin;
};

}

#endif

