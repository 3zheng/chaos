CREATE TABLE [dbo].[round_details_user_relation]
(
	[Id] INT NOT NULL PRIMARY KEY, 
    [plan_id] INT NOT NULL, 
    [match_id] BIGINT NOT NULL, 
    [round_id] VARCHAR(50) NOT NULL, 
    [user_id] BIGINT NOT NULL, 
    [round_result] INT NOT NULL DEFAULT 0
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'每局局况记录的用户索引表',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'round_details_user_relation',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'表记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'round_details_user_relation',
    @level2type = N'COLUMN',
    @level2name = N'Id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'round_details_user_relation',
    @level2type = N'COLUMN',
    @level2name = N'plan_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'比赛id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'round_details_user_relation',
    @level2type = N'COLUMN',
    @level2name = N'match_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'局id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'round_details_user_relation',
    @level2type = N'COLUMN',
    @level2name = N'round_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'round_details_user_relation',
    @level2type = N'COLUMN',
    @level2name = N'user_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'胜负结果 1胜 2平 3负',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'round_details_user_relation',
    @level2type = N'COLUMN',
    @level2name = N'round_result'