bin_PROGRAMS=indigoplayer

indigoplayer_SOURCES=../src/Capital.cpp ../src/ConfigFile.cpp  \
../src/ClassHelper/ClassHelper.cpp \
../src/DataStructures/GraphicData.cpp ../src/DataStructures/LoadedStreams.cpp \
../src/DataStructures/PlayParameters.cpp \
../src/Files/FileUtilities.cpp ../src/Files/IndigoFile.cpp ../src/Files/Logger.cpp \
../src/Files/PathLoader.cpp ../src/OneInstance.cpp \
../src/Graphic/ControlPanel.cpp ../src/Graphic/OpenFileDialog.cpp ../src/Graphic/Options.cpp \
../src/Graphic/PlayerWindow.cpp ../src/Graphic/PlaylistGraphic.cpp \
../src/Graphic/ThisOptions.cpp ../src/Graphic/ThisOptionsLoad.cpp ../src/Graphic/VideoBoard.cpp \
../src/GraphicLogic/GraphicLoader.cpp ../src/GraphicLogic/Playlist.cpp ../src/GraphicLogic/WindowBridge.cpp \
../src/GraphicLogic/GraphicPathLoader.cpp \
../src/Interfaces/Bridge.cpp ../src/Interfaces/Callable.cpp ../src/Interfaces/PlayerSignals.cpp ../src/Interfaces/VideoFilters.cpp \
../src/MyWidget/FileChoosers.cpp ../src/MyWidget/MyComboBox.cpp \
../src/Player/ColorSetings.cpp ../src/Player/IndigoPlayer.cpp ../src/Player/OneFilePlayer.cpp \
../src/Player/SavedFileInfo.cpp ../src/Player/ShortKeys.cpp \
../src/PlayerKernel/MediaPackage.cpp ../src/PlayerKernel/MplayerInterface.cpp ../src/PlayerKernel/PlayerKernel.cpp \
../src/PlayerKernel/ScriptGenerator.cpp

AM_CXXFLAGS = $(DEPS_CFLAGS) -DDATADIR=\"$(datadir)\" -lrt
indigoplayer_LDADD = $(DEPS_LIBS)
