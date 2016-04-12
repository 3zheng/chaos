CREATE TABLE [dbo].[game_round_details]
(
	[Id] INT NOT NULL PRIMARY KEY IDENTITY, 
    [plan_id] INT NOT NULL, 
    [match_id] BIGINT NOT NULL, 
    [round_id] VARCHAR(50) NOT NULL, 
    [round_details] TEXT NULL, 
    [game_kind] INT NULL 
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'表记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'game_round_details',
    @level2type = N'COLUMN',
    @level2name = N'Id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'game_round_details',
    @level2type = N'COLUMN',
    @level2name = N'plan_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'比赛id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'game_round_details',
    @level2type = N'COLUMN',
    @level2name = N'match_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'局id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'game_round_details',
    @level2type = N'COLUMN',
    @level2name = N'round_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'局况记录',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'game_round_details',
    @level2type = N'COLUMN',
    @level2name = N'round_details'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'游戏类型',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'game_round_details',
    @level2type = N'COLUMN',
    @level2name = N'game_kind'