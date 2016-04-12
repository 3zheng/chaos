CREATE TABLE [dbo].[user_fund_log]
(
	[R_Id] BIGINT NOT NULL PRIMARY KEY IDENTITY, 
    [user_id] BIGINT NOT NULL, 
    [fund_id] INT NOT NULL, 
    [change_count] BIGINT NOT NULL, 
    [old_count] BIGINT NOT NULL DEFAULT 1, 
    [current_count] BIGINT NOT NULL, 
    [r_create_time] DATETIME NULL DEFAULT getdate(), 
    [reason_type] INT NOT NULL, 
    [reason_att_id] INT NULL DEFAULT 0, 
    [att_content] VARCHAR(100) NULL, 
    [app_type] INT NULL, 
    [app_id] INT NULL, 
    [fund_status] INT NOT NULL DEFAULT 1, 
    [db_session_id] BIGINT NOT NULL DEFAULT 0 


)
go
create index [index_reason_type] on [dbo].[user_fund_log]([reason_type])

go
create index [index_user_fund] on [dbo].[user_fund_log]([user_id], [fund_id])

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户的财富流水记录',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'记录id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'R_Id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'user_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'财富类型',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = 'fund_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'变更数量',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = 'change_count'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'变更前数量',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = 'old_count'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'变更后数量',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'current_count'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'创建时间',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'r_create_time'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'详情见fund.proto',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'reason_type'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'reason_type的关联id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = 'reason_att_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'附录说明描述',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = 'att_content'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'请求财富变更的APP TYPE',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'app_type'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'请求财富变更的APP ID',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'app_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N' 1有效 2无效 给外部财富（金币）用',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = 'fund_status'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'由程序赋值，为了在更改表记录的fund_status值时，是通过这个字段来找到对应的表记录',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'user_fund_log',
    @level2type = N'COLUMN',
    @level2name = N'db_session_id'
GO

CREATE INDEX [index_db_session] ON [dbo].[user_fund_log] ([db_session_id])
