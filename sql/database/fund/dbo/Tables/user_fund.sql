CREATE TABLE [dbo].[user_fund]
(
	[R_Id] BIGINT NOT NULL PRIMARY KEY IDENTITY, 
    [user_id] BIGINT NULL, 
    [fund_id] INT NULL, 
    [fund_count] BIGINT NULL, 
    [up_code] INT NULL, 
    [modify_time] DATETIME NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户的财富表',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund',
    @level2type = N'COLUMN',
    @level2name = N'R_Id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund',
    @level2type = N'COLUMN',
    @level2name = N'user_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'财富类型',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund',
    @level2type = N'COLUMN',
    @level2name = 'fund_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'财富数量',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund',
    @level2type = N'COLUMN',
    @level2name = N'fund_count'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'更新次数，每更新一次+1',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund',
    @level2type = N'COLUMN',
    @level2name = N'up_code'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'最后一次修改时间',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund',
    @level2type = N'COLUMN',
    @level2name = N'modify_time'
GO

CREATE INDEX [Index_userid_fundid] ON [dbo].[user_fund] ([user_id], [fund_id])
