CREATE TABLE [dbo].[tgame_version]
(
  [record_id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [game_kind] INT NOT NULL DEFAULT 0, 
    [version_min] INT NOT NULL DEFAULT 0, 
    [version_current] INT NOT NULL DEFAULT 0, 
    [client_os] INT NOT NULL DEFAULT 1, 
    [notes] VARCHAR(50) NULL, 
    [download_url] VARCHAR(200) NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'游戏类型',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'tgame_version',
    @level2type = N'COLUMN',
    @level2name = N'game_kind'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'支持的最低版本',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'tgame_version',
    @level2type = N'COLUMN',
    @level2name = N'version_min'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'当前版本',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'tgame_version',
    @level2type = N'COLUMN',
    @level2name = N'version_current'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'客户端类型 =1 表示win,2 =win10 4=android 8= ios',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'tgame_version',
    @level2type = N'COLUMN',
    @level2name = N'client_os'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'说明',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'tgame_version',
    @level2type = N'COLUMN',
    @level2name = N'notes'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'下载新地址',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'tgame_version',
    @level2type = N'COLUMN',
    @level2name = N'download_url'