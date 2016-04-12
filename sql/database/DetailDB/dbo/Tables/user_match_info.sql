CREATE TABLE [dbo].[user_match_info]
(
	[Id] BIGINT NOT NULL PRIMARY KEY IDENTITY(100, 1), 
    [user_id] BIGINT NOT NULL, 
    [plan_id] INT NOT NULL, 
    [match_id] BIGINT NOT NULL, 
    [plan_name] VARCHAR(50) NOT NULL, 
    [match_rank] INT NOT NULL, 
    [end_date] BIGINT NOT NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'表记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = N'COLUMN',
    @level2name = N'Id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = N'COLUMN',
    @level2name = N'user_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = N'COLUMN',
    @level2name = N'plan_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'比赛id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = N'COLUMN',
    @level2name = N'match_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事名字',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = N'COLUMN',
    @level2name = N'plan_name'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'名次',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = N'COLUMN',
    @level2name = 'match_rank'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'获得名次时的时间，格式YYYYMMDDHHMMSS',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = N'COLUMN',
    @level2name = N'end_date'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户比赛数据',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_match_info',
    @level2type = NULL,
    @level2name = NULL