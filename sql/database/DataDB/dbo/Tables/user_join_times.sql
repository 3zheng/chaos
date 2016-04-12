CREATE TABLE [dbo].[user_join_times]
(
	[Id] BIGINT NOT NULL PRIMARY KEY IDENTITY(100, 1), 
    [user_id] BIGINT NOT NULL, 
    [today_join_times] INT NOT NULL, 
	[total_join_times] INT NOT NULL, 
    [join_date] INT NOT NULL, 
    [plan_id] INT NOT NULL, 
    [game_kind] INT NOT NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = N'COLUMN',
    @level2name = N'Id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = N'COLUMN',
    @level2name = N'user_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'今日参赛次数',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = N'COLUMN',
    @level2name = 'today_join_times'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'参赛更新日期，格式YYYYMMDD',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = N'COLUMN',
    @level2name = 'join_date'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户参赛次数',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = N'COLUMN',
    @level2name = N'plan_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'游戏类型',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = N'COLUMN',
    @level2name = N'game_kind'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'总参赛次数',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_join_times',
    @level2type = N'COLUMN',
    @level2name = N'total_join_times'
GO

CREATE INDEX [IX_user_join_times_Column] ON [dbo].[user_join_times] ([user_id])
