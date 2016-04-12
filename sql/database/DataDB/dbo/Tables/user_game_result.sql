CREATE TABLE [dbo].[user_game_result]
(
	[Id] BIGINT NOT NULL PRIMARY KEY IDENTITY, 
    [user_id] BIGINT NOT NULL, 
    [win_times] INT NOT NULL DEFAULT 0, 
    [draw_times] INT NOT NULL DEFAULT 0, 
    [lose_times] INT NOT NULL DEFAULT 0, 
    [game_kind] INT NOT NULL
)


GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'表记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_game_result',
    @level2type = N'COLUMN',
    @level2name = N'Id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_game_result',
    @level2type = N'COLUMN',
    @level2name = N'user_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赢的次数',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_game_result',
    @level2type = N'COLUMN',
    @level2name = N'win_times'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'平的次数',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_game_result',
    @level2type = N'COLUMN',
    @level2name = N'draw_times'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'输的次数',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_game_result',
    @level2type = N'COLUMN',
    @level2name = N'lose_times'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'游戏类型',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_game_result',
    @level2type = N'COLUMN',
    @level2name = N'game_kind'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户胜负平局数记录',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_game_result',
    @level2type = NULL,
    @level2name = NULL
GO



CREATE INDEX [IX_user_game_result_Column] ON [dbo].[user_game_result] ([user_id])
