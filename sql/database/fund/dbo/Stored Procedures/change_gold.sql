CREATE PROCEDURE [dbo].[change_gold]
	@Action int, /*动作  0 扣币,1加币*/
	@App int,  /*应用ID*/
	@UserID bigint, /*用户ID*/
	@TargetUserID bigint, /*目标帐户ID*/
	@ObjectID int, /* 对像ID(道具ID，礼物ID等)*/
	@ObjectNum int,/* 对像数量*/
	@ScoreChange bigint,/*币操作金额*/
	@GameID int,	/*游戏ID*/
	@KindID int,	/*房间ID*/
	@Descpt varchar(256), /*描述说明*/
	@Prm1 varchar(256),		/*备用1*/
	@Prm2 varchar(256),		/*备用2*/
	@Prm3 varchar(256),		/*备用3*/
	@Prm4 varchar(256),		/*备用4*/
	@Returnprm nvarchar(256) output, /*输出备用*/
	@Ret int output,			/*结果:1成功  -1  操作失败   -2余额不足, -3加币失败,-4参数错误,-5APP不存在,-6超出当日交易限额*/
	@Retmessage nvarchar(50) output /*成功返回操作后余额，失败则返回失败信息*/
AS
--由于C程序不支持varchar的输出参数，所以只能使用nvarchar类型，要做一次转换
--set @Returnprm = 'aa';
--
--set @Retmessage = 'good';
	declare @Returnprm_tmp varchar(256)
	declare @Retmessage_tmp varchar(50)

	EXEC [QPTreasureDBLink].QPTreasureDB.DBO.GSP_Common_AccountScoreChange @Action, @App, @UserID, @TargetUserID, @ObjectID, @ObjectNum, @ScoreChange, @GameID,
		@KindID, @Descpt, @Prm1, @Prm2, @Prm3, @Prm4, @Returnprm_tmp output, @Ret output, @Retmessage_tmp output;

	set @Returnprm = @Returnprm_tmp;
	set @Retmessage = @Retmessage_tmp;
RETURN 0
