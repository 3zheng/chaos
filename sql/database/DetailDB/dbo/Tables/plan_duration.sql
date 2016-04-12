CREATE TABLE [dbo].[plan_duration]
(
	[Id] BIGINT NOT NULL PRIMARY KEY IDENTITY, 
    [plan_id] INT NOT NULL, 
    [match_id] BIGINT NOT NULL, 
    [mass_election_duration] INT NOT NULL, 
    [elimination_duration] INT NOT NULL, 
    [match_date] BIGINT NOT NULL, 
    [create_date] DATETIME NULL DEFAULT getdate()
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'比赛阶段耗时',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'plan_duration',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'赛事id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'plan_duration',
    @level2type = N'COLUMN',
    @level2name = N'plan_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'比赛id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'plan_duration',
    @level2type = N'COLUMN',
    @level2name = N'match_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'海选阶段耗时',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'plan_duration',
    @level2type = N'COLUMN',
    @level2name = 'mass_election_duration'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'淘汰赛阶段耗时',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'plan_duration',
    @level2type = N'COLUMN',
    @level2name = 'elimination_duration'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'比赛结束的时间YYYYMMDDHHMMSS',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'plan_duration',
    @level2type = N'COLUMN',
    @level2name = N'match_date'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'表记录创建时间',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'plan_duration',
    @level2type = N'COLUMN',
    @level2name = N'create_date'